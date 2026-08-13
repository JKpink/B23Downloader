#!/usr/bin/env bash
#
# B23Downloader macOS 打包脚本
#
# 用法:
#   ./mac_package.sh              # 完整构建 + 打 .dmg
#   ./mac_package.sh --app-only   # 只构建并部署 app（不打 dmg）
#
# 环境变量:
#   QT_BIN=/path/to/qmake6   # 指定 Qt 位置（默认自动找 qmake6 / qmake）
#
# 产物:
#   B23Downloader.app                          (构建目录内，已内嵌 Qt 框架)
#   dist/B23Downloader-<版本>-macOS-<架构>.dmg (可分发)
#
# 依赖: Qt 6 (qmake、macdeployqt)、Xcode Command Line Tools (make/clang/codesign/hdiutil)
#
# 注: Windows 上对应的工具是 windeployqt（与 MSVC/mingw 配合使用），本脚本仅覆盖 macOS。
set -euo pipefail

SRC_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PRO_DIR="$SRC_DIR/B23Downloader"
APP_BUNDLE="$PRO_DIR/B23Downloader.app"
DIST_DIR="$SRC_DIR/dist"
ONLY_APP=0
[[ "${1:-}" == "--app-only" ]] && ONLY_APP=1

# ---------- 1. 定位 Qt ----------
QMAKE="${QT_BIN:-}"
if [[ -z "$QMAKE" ]]; then
    QMAKE="$(command -v qmake6 || command -v qmake || true)"
fi
if [[ -z "$QMAKE" ]]; then
    echo "错误: 找不到 qmake6/qmake，请设置 QT_BIN=/path/to/qmake6" >&2
    exit 1
fi
QT_BIN_DIR="$(dirname "$QMAKE")"
MACDEPLOYQT="$QT_BIN_DIR/macdeployqt"
if [[ ! -x "$MACDEPLOYQT" ]]; then
    echo "错误: 找不到 macdeployqt: $MACDEPLOYQT" >&2
    exit 1
fi
echo "==> Qt: $QT_BIN_DIR"

# ---------- 2. 编译 ----------
cd "$PRO_DIR"
"$QMAKE" B23Downloader.pro
make clean
make -j"$(sysctl -n hw.ncpu)"
echo "==> 编译完成"

# ---------- 3. 部署 Qt 框架与插件 ----------
"$MACDEPLOYQT" "$APP_BUNDLE"

# macdeployqt 对 Homebrew 分散安装的 qtsvg 支持不稳，可能漏掉 SVG 支持
# (工具栏图标都是 .svg，缺了 libqsvg 插件图标会空白)，手动补装:
SVG_PLUGIN="/opt/homebrew/share/qt/plugins/imageformats/libqsvg.dylib"
if [[ -f "$SVG_PLUGIN" && ! -f "$APP_BUNDLE/Contents/PlugIns/imageformats/libqsvg.dylib" ]]; then
    echo "==> 补装 qsvg 插件 + QtSvg 框架"
    cp "$SVG_PLUGIN" "$APP_BUNDLE/Contents/PlugIns/imageformats/"
    cp -R "/opt/homebrew/lib/QtSvg.framework" "$APP_BUNDLE/Contents/Frameworks/"
    install_name_tool -change @rpath/QtSvg.framework/Versions/A/QtSvg \
        @executable_path/../Frameworks/QtSvg.framework/Versions/A/QtSvg \
        "$APP_BUNDLE/Contents/PlugIns/imageformats/libqsvg.dylib"
    install_name_tool -id @rpath/QtSvg.framework/Versions/A/QtSvg \
        "$APP_BUNDLE/Contents/Frameworks/QtSvg.framework/Versions/A/QtSvg"
    install_name_tool -change /opt/homebrew/opt/qtbase/lib/QtGui.framework/Versions/A/QtGui \
        @executable_path/../Frameworks/QtGui.framework/Versions/A/QtGui \
        "$APP_BUNDLE/Contents/Frameworks/QtSvg.framework/Versions/A/QtSvg"
    install_name_tool -change /opt/homebrew/opt/qtbase/lib/QtCore.framework/Versions/A/QtCore \
        @executable_path/../Frameworks/QtCore.framework/Versions/A/QtCore \
        "$APP_BUNDLE/Contents/Frameworks/QtSvg.framework/Versions/A/QtSvg"
fi

# qmake 生成的 Info.plist 图标字段可能为空，手动补上
if [[ "$(plutil -extract CFBundleIconFile raw "$APP_BUNDLE/Contents/Info.plist" 2>/dev/null)" != "B23Downloader" ]]; then
    plutil -replace CFBundleIconFile -string B23Downloader "$APP_BUNDLE/Contents/Info.plist"
fi

codesign --force --sign - "$APP_BUNDLE" 2>/dev/null || true   # ad-hoc 签名，本地可直接运行

# 检查是否还有漏打包的 homebrew 动态库（理论上 macdeployqt 应全部处理）
UNRESOLVED="$(otool -L "$APP_BUNDLE/Contents/MacOS/B23Downloader" | grep '/opt/homebrew' || true)"
if [[ -n "$UNRESOLVED" ]]; then
    echo "警告: 仍有未打包的 homebrew 库，可能需要手工处理:" >&2
    echo "$UNRESOLVED" >&2
fi
echo "==> 部署完成: $APP_BUNDLE"

if [[ "$ONLY_APP" == 1 ]]; then
    exit 0
fi

# ---------- 4. 打 .dmg ----------
VERSION="$(sed -n 's/^VERSION[[:space:]]*=[[:space:]]*//p' "$PRO_DIR/B23Downloader.pro" | head -1)"
STAGING="$(mktemp -d /tmp/b23dmg.XXXXXX)"
trap 'rm -rf "$STAGING"' EXIT
cp -R "$APP_BUNDLE" "$STAGING/"
ln -s /Applications "$STAGING/Applications"      # dmg 里的 Applications 快捷方式

mkdir -p "$DIST_DIR"
DMG_NAME="B23Downloader-${VERSION}-macOS-$(uname -m).dmg"
hdiutil create -volname "B23Downloader" -srcfolder "$STAGING" \
    -ov -format UDZO "$DIST_DIR/$DMG_NAME"

echo "==> 完成: $DIST_DIR/$DMG_NAME"
open "$DIST_DIR"
