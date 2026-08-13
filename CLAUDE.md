# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

B23Downloader is a Qt Widgets desktop app (C++17, qmake) that downloads videos, live streams, and manga from Bilibili. All user-facing strings, error messages, and most comments are in Chinese; identifiers are English camelCase. The README (Chinese) documents the supported URL formats and known quirks.

The git repo root is `B23Downloader/` (the enclosing `mimi/` directory is not part of the repo). The repo is dormant — last commit Feb 2022.

## Build & run

Requires Qt 6 (Core, Gui, Network, Widgets — no Multimedia) and OpenSSL at runtime (all requests are HTTPS; on Windows "TLS initialization failed" means the OpenSSL DLLs are missing — see README "Build-Issues").

```sh
cd B23Downloader/B23Downloader
qmake6 B23Downloader.pro   # or qmake, if only one Qt is installed
make                       # mingw32-make / nmake on Windows
./B23Downloader
```

- Only build file: `B23Downloader/B23Downloader.pro` (no CMake, no `.ui` files — all UI is hand-coded). Icons come from `icons.qrc`.
- Version `0.9.5` is set in the .pro (`VERSION`); on Linux it reaches the app via the `APP_VERSION` define.
- There are no tests, no CI, no linter. Verify changes manually: run the app, paste a bilibili URL, check the downloaded files.
- Note: the .pro says `CONFIG += c++11`, but the README's C++17 statement reflects the actual toolchain in use.

## Architecture

Single-threaded and fully async: no QThreads; every HTTP request is a `QNetworkReply` on the one global `QNetworkAccessManager` from `Network::accessManager()`. At most 3 downloads run concurrently (`MaxConcurrentTaskCount` in `TaskTable.cpp`); extra tasks wait in a `Waiting` state.

### Data flow (URL → file)

1. `MainWindow` passes the pasted URL to `DownloadDialog`, which runs `Extractor::start(url)`.
2. `Extractor` (`Extractor.cpp`) matches bare IDs (`BV…`/`av…`/`ss…`/`ep…`/`live…`) or dispatches on host/path via regex (video, bangumi, cheese courses, live incl. activity pages, comic, b23.tv/b22.top short links). Each step is one HTTP request; some flows chain a second one (media_id → season_id, activity page → room_id; redirects are resolved manually since auto-redirect is disabled). It emits a `Result` describing episodes, with flags `VipOnly` / `PayOnly` / `AllowWaitFree` / `Disabled`.
3. On OK, `DownloadDialog::getDownloadTasks()` creates one `AbstractDownloadTask` per selected episode and hands them to `TaskTableWidget::addTasks()`.
4. Task subclasses in `DownloadTask.cpp`:
   - `VideoDownloadTask` (shared by UGC/PGC/PUGV): play-url API → stream the `QNetworkReply` straight into a `QFile` via `readyRead`. Resume = reopen the file, seek to the saved `downloadedBytesCnt`, send a `Range: bytes=N-` header.
   - `LiveDownloadTask`: the stream is fed into `FlvLiveDownloadDelegate` (`Flv.cpp`), which remuxes while writing: resets the timestamp base to 0, patches `onMetaData` with a `keyframes` table (times/filepositions + pre-allocated spacer arrays, ~100 KB, covers ~5 h at 3 s keyframe intervals — both use self-patching anchors), and starts a new file when the keyframe arrays fill. Uses the vendored AMF0 implementation in `Flv.cpp`; rejects HEVC.
   - `ComicDownloadTask`: per image — POST `GetImageIndex` → POST `ImageToken` → GET `url?token=` → write via `QSaveFile`. Output is zero-padded `01.jpg`… inside `<title> <ep>/`.
5. Progress/ETA are polled by a 500 ms timer in `TaskCellWidget`; finished rows auto-remove after 3 s; the task list auto-saves every 5 s.

### Network layer (`Network.cpp`)

- `Network::Bili::Request` centralizes spoofing: Chrome/Edge 90 User-Agent, Referer `https://www.bilibili.com`, `setMaximumRedirectsAllowed(0)`.
- `Network::Bili::parseReply` unwraps the bilibili envelope (`code`/`message`) into Chinese `QString` errors. The network layer does not retry; retry-on-failure is up to callers (e.g. MainWindow re-queries user info every 10 s).

### Persistence & login

- `Settings` (`Settings.cpp`) is a `QSettings(IniFormat, UserScope, "VoidZero", "B23Downloader")` singleton (`Settings::inst()`). Keys: `cookies`, `tasks` (JSON serialization of in-flight tasks, enabling resume), `lastDir`. Live tasks are deliberately never persisted. The download dialog's default directory is `QStandardPaths::DownloadLocation` (`~/Downloads`), falling back to `<appDir>/Downloads`; `lastDir` is only written when a task is created (`DownloadDialog::getDownloadTasks`).
- QR login: `LoginDialog` + vendored Nayuki generator (`QrCode.cpp`) — GET `x/passport-login/web/qrcode/generate`, render the QR in Bilibili pink, poll GET `x/passport-login/web/qrcode/poll?qrcode_key=…` every 2 s (`data.code`: 0 = confirmed, 86101 = not scanned, other states are decoded from `data.message`). On success the session cookies (SESSDATA, bili_jct, DedeUserID…) are parsed from `data.url`'s query params into the CookieJar — they are not conveyed by Set-Cookie alone. Logout POSTs `biliCSRF=<bili_jct cookie>`; `CookieJar` is installed on the QNAM by MainWindow.
- `main.cpp`: Windows-only single-instance guard via `QSharedMemory("B23Dld-HWND")`; a second launch raises the existing window and exits. No guard on other platforms.

### Bilibili API endpoints

- Metadata: `api.bilibili.com/x/web-interface/view` (UGC), `pgc/view/web/season` (bangumi), `pgc/review/user` (media_id → season_id), `pgc/view/web/season/user/status` (VIP/pay), `pugv/view/web/season` (courses), `api.live.bilibili.com/xlive/web-room/v1/index/getInfoByRoom`, `manga.bilibili.com/twirp/comic.v1.Comic/ComicDetail` (POST).
- Play URLs (also reused by DownloadDialog for the quality list): `x/player/playurl` (UGC, key `data`), `pgc/player/web/playurl` (key `result`), `pugv/player/web/playurl` (key `data`), `api.live.bilibili.com/xlive/web-room/v2/index/getRoomPlayInfo`.
- Comic download: `GetImageIndex`, `ImageToken` (both POST), then GET the image with `?token=` appended.
- Auth: `passport.bilibili.com/x/passport-login/web/qrcode/generate` / `poll` (the old `qrcode/getLoginUrl` + `getLoginInfo` pair is retired — do not use), `api.bilibili.com/nav`, `passport.bilibili.com/login/exit/v2`.

## Conventions & gotchas

- Async idiom: each class keeps one reusable `QNetworkReply *httpReply` member; initiating methods are `startXxx`, handlers are `xxxFinished` (null the member + `deleteLater()`); treat `QNetworkReply::OperationCanceledError` as a silent no-op (the universal cancel signal). Errors surface as Chinese `QString`s via `errorOccurred` signals → red `ElidedTextLabel` or `QMessageBox::critical`.
- Before touching FLV remuxing (`Flv.cpp`) or the single-instance code (`main.cpp`), read the corresponding dev-log sections in README.md — they explain the non-obvious design (live-FLV seekability, QSharedMemory + Windows foreground restrictions).
- Deliberate behaviors, don't "fix" them: comic task removal recursively deletes the episode folder; pausing a live task and restarting writes a brand-new file (live never resumes); live tasks are not restored after restart; interactive videos (互动视频) and Vomic are rejected by the extractor.
- Some disabled code exists: the `ENABLE_UPDATE_CHECK` define is commented out in the .pro, and `AboutWidget` contains update-check logic under that macro.
