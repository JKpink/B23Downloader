#include "LoginDialog.h"
#include "Network.h"
#include "QrCode.h"
#include "Settings.h"

#include <QtWidgets>
#include <QtNetwork>
#include <QDataStream>
#include <QUrlQuery>
#include <QDateTime>

static constexpr int QrCodeExpireTime = 180; // seconds
static constexpr int PollInterval = 2000; // ms
static constexpr int MaxPollTimes = (QrCodeExpireTime * 1000 / PollInterval) - 3;
static constexpr QColor QrCodeColor = QColor(251, 114, 153); // B站粉

static constexpr auto ScanToLoginTip = "请使用B站客户端<br>扫描二维码登录";

LoginDialog::LoginDialog(QWidget *parent)
  : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    qrCodeLabel = new QLabel(this);
    qrCodeLabel->setFixedSize(123, 123);
    qrCodeLabel->setAlignment(Qt::AlignCenter);
    tipLabel= new QLabel(ScanToLoginTip, this);
    tipLabel->setAlignment(Qt::AlignCenter);
    auto font = tipLabel->font();
    font.setPointSize(11);
    tipLabel->setFont(font);

    refreshButton = new QToolButton(qrCodeLabel);
    refreshButton->setStyleSheet("background-color: white; border: 2px solid #cccccc;");
    refreshButton->setCursor(Qt::PointingHandCursor);
    refreshButton->setIcon(QIcon(":/icons/refresh.png"));
    refreshButton->setIconSize(QSize(32, 32));
    refreshButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    refreshButton->setText("点击刷新");
    refreshButton->setHidden(true);
    connect(refreshButton, &QToolButton::clicked, this, [this]() {
        hideRefreshButton();
        startGetLoginUrl();
    });

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(qrCodeLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(tipLabel, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    setWindowTitle("B站登录");

    pollTimer = new QTimer(this);
    pollTimer->setInterval(PollInterval);
    pollTimer->setSingleShot(true);
    connect(pollTimer, &QTimer::timeout, this, &LoginDialog::pollLoginInfo);

    startGetLoginUrl();
}

void LoginDialog::closeEvent(QCloseEvent *e)
{
    if (httpReply != nullptr) {
        httpReply->abort();
        httpReply = nullptr;
    }
    QDialog::closeEvent(e);
}

LoginDialog::~LoginDialog() = default;

void LoginDialog::showRefreshButton()
{
    refreshButton->setHidden(false);
    refreshButton->move(qrCodeLabel->rect().center() - refreshButton->rect().center());
}

void LoginDialog::hideRefreshButton()
{
    refreshButton->setHidden(true);
}

void LoginDialog::qrCodeExpired()
{
    // blur the QR code
    QPixmap pixmap = qrCodeLabel->pixmap();
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(255, 255, 255, 196)));
    painter.drawRect(QRect(QPoint(0, 0), pixmap.size()));
    qrCodeLabel->setPixmap(pixmap);

    tipLabel->setText("二维码已失效");
    showRefreshButton();
}

// if error occured, handle the error and return empty object
QJsonValue LoginDialog::getReplyData()
{
    auto reply = httpReply;
    httpReply->deleteLater();
    httpReply = nullptr;

    if (reply->error() == QNetworkReply::OperationCanceledError) {
        // aborted (in close event)
        return QJsonValue();
    }

    const auto [json, errorString] = Network::Bili::parseReply(reply, "data");
    if (!errorString.isNull()) {
        tipLabel->setText(errorString);
        showRefreshButton();
        return QJsonValue();
    }

    return json["data"];
}

void LoginDialog::startGetLoginUrl()
{
    httpReply = Network::Bili::get("https://passport.bilibili.com/x/passport-login/web/qrcode/generate");
    connect(httpReply, &QNetworkReply::finished, this, &LoginDialog::getLoginUrlFinished);
}

void LoginDialog::getLoginUrlFinished()
{
    auto data = getReplyData().toObject();
    if (data.isEmpty()) {
        // network error
        return;
    }

    QString url = data["url"].toString();
    qrcodeKey = data["qrcode_key"].toString();
    if (qrcodeKey.isEmpty()) {
        tipLabel->setText("获取二维码失败");
        showRefreshButton();
        return;
    }
    setQrCode(url);
    tipLabel->setText(ScanToLoginTip);
    polledTimes = 0;
    pollTimer->start();
}

void LoginDialog::pollLoginInfo()
{
    QUrl url("https://passport.bilibili.com/x/passport-login/web/qrcode/poll");
    QUrlQuery query;
    query.addQueryItem("qrcode_key", qrcodeKey);
    url.setQuery(query);
    httpReply = Network::Bili::get(url);
    connect(httpReply, &QNetworkReply::finished, this, &LoginDialog::getLoginInfoFinished);
}

void LoginDialog::getLoginInfoFinished()
{
    polledTimes++;
    auto data = getReplyData();
    if (data.isNull() || data.isUndefined()) {
        // network error, keep polling
        pollTimer->start();
        return;
    }

    auto dataObj = data.toObject();
    bool isPollEnded = false;
    int pollCode = dataObj["code"].toInt(-1);
    QString pollMsg = dataObj["message"].toString();
    if (pollCode == 0) {
        // scanned and confirmed
        isPollEnded = true;
        saveLoginCookies(dataObj["url"].toString());
        accept();
    } else if (pollCode == 86101) {
        // qrcode not scanned
    } else {
        // scanned but not confirmed, or expired, etc.
        if (pollMsg.contains("确认")) {
            tipLabel->setText("✅扫描成功<br>请在手机上确认");
        } else {
            tipLabel->setText(pollMsg);
        }
        if (pollMsg.contains("失效")) {
            isPollEnded = true;
            qrCodeExpired();
        }
    }

    if (!isPollEnded) {
        if (polledTimes == MaxPollTimes) {
            qrCodeExpired();
        } else {
            pollTimer->start();
        }
    }
}

// session cookies are conveyed in the sso url returned by the poll api,
// (and/or in Set-Cookie headers, which the QNAM cookie jar captures automatically)
void LoginDialog::saveLoginCookies(const QString &ssoUrl)
{
    if (ssoUrl.isEmpty()) {
        return;
    }
    auto urlQuery = QUrlQuery(QUrl(ssoUrl));
    QList<QNetworkCookie> loginCookies;
    for (const char *name : {"DedeUserID", "DedeUserID__ckMd5", "SESSDATA", "bili_jct"}) {
        auto value = urlQuery.queryItemValue(name);
        if (value.isEmpty()) {
            continue;
        }
        QNetworkCookie cookie(QByteArray(name), value.toUtf8());
        cookie.setDomain(".bilibili.com");
        cookie.setPath("/");
        cookie.setSecure(qstrcmp(name, "SESSDATA") == 0 || qstrcmp(name, "bili_jct") == 0);
        auto expires = urlQuery.queryItemValue("Expires");
        if (!expires.isEmpty()) {
            cookie.setExpirationDate(QDateTime::fromSecsSinceEpoch(expires.toLongLong()));
        }
        loginCookies.append(cookie);
    }
    if (!loginCookies.isEmpty()) {
        Settings::inst()->getCookieJar()->addCookies(loginCookies);
    }
}

void LoginDialog::setQrCode(const QString &content)
{
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(content.toUtf8(), QrCode::Ecc::MEDIUM);
    int n = qr.getSize();

    QPixmap pixmap(n * 3, n * 3);
    QPainter painter(&pixmap);
    QPen pen(QrCodeColor);
    pen.setWidth(3);
    painter.setPen(pen);

    pixmap.fill();
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            auto val = qr.getModule(col, row);
            if (val) {
                painter.drawPoint(row * 3 + 1, col * 3 + 1);
            }
        }
    }

    qrCodeLabel->setFixedSize(pixmap.size());
    qrCodeLabel->setPixmap(pixmap);
}
