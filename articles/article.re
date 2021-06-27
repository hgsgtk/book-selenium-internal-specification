
= Selenium

https://www.codegrid.net/articles/2014-selenium-1/

== Selenium 1,2,3

Selenium の歴史

https://www.selenium.dev/history/

Selenium のバージョン

現在は Selenium 3 である。
その歴史的変遷。

歴史について、Selenium Coreの時代
[https://blog.trident-qa.com/2013/05/so-many-seleniums/](https://blog.trident-qa.com/2013/05/so-many-seleniums/)

W3Cでの標準化の結果は？

=== Remote Driver

Selenium ServerでのRemote Driverについて

[https://www.selenium.dev/documentation/ja/legacy_docs/remote_webdriver_server/](https://www.selenium.dev/documentation/ja/legacy_docs/remote_webdriver_server/)

=== W3CのDriver

W3CのDriverについて

[https://w3c.github.io/webdriver/webdriver-spec.html#protocol](https://w3c.github.io/webdriver/webdriver-spec.html#protocol)

=== Protocol

Selenium Serverとドライバは当然JSON Wire Protocolで通信しますが、クライアントとSelenium Server同士もJSON Wire Protocolでリクエストを行います。

WebDriverの通信方式 JSON Wire Protocolとは？今も現役？つかってなさそうかな？
今は使っていない、W3CのWeb Driver仕様

=== Selenium Server

- start selenium server by Docker

```bash
$ docker run -d -p 4444:4444 -v /dev/shm:/dev/shm selenium/standalone-chrome:4.0.0-rc-1-prerelease-20210618
```

ref: https://github.com/SeleniumHQ/docker-selenium

```
$ docker logs 473fe763ab06
2021-06-26 07:00:21,642 INFO Included extra file "/etc/supervisor/conf.d/selenium.conf" during parsing
2021-06-26 07:00:21,644 INFO supervisord started with pid 9
2021-06-26 07:00:22,653 INFO spawned: 'xvfb' with pid 11
2021-06-26 07:00:22,658 INFO spawned: 'vnc' with pid 12
2021-06-26 07:00:22,661 INFO spawned: 'novnc' with pid 13
2021-06-26 07:00:22,665 INFO spawned: 'selenium-standalone' with pid 14
2021-06-26 07:00:22,685 INFO success: xvfb entered RUNNING state, process has stayed up for > than 0 seconds (startsecs)
2021-06-26 07:00:22,685 INFO success: vnc entered RUNNING state, process has stayed up for > than 0 seconds (startsecs)
2021-06-26 07:00:22,685 INFO success: novnc entered RUNNING state, process has stayed up for > than 0 seconds (startsecs)
2021-06-26 07:00:22,685 INFO success: selenium-standalone entered RUNNING state, process has stayed up for > than 0 seconds (startsecs)
Selenium Grid Standalone configuration:
[network]
relax-checks = true

[node]
session-timeout = "300"
override-max-sessions = false
detect-drivers = false
max-sessions = 1

[[node.driver-configuration]]
name = "chrome"
stereotype = '{"browserName": "chrome", "browserVersion": "91.0", "platformName": "Linux"}'
max-sessions = 1

Starting Selenium Grid Standalone...
07:00:23.285 INFO [LoggingOptions.configureLogEncoding] - Using the system default encoding
07:00:23.291 INFO [OpenTelemetryTracer.createTracer] - Using OpenTelemetry for tracing
07:00:24.296 INFO [NodeOptions.getSessionFactories] - Detected 4 available processors
07:00:24.369 INFO [NodeOptions.report] - Adding chrome for {"browserVersion": "91.0","browserName": "chrome","platformName": "Linux","se:vncEnabled": true} 1 times
07:00:24.392 INFO [Node.<init>] - Binding additional locator mechanisms: id, name
07:00:24.415 INFO [LocalDistributor.add] - Added node 218787d9-1433-40fc-a6c2-792e573c1a68 at http://172.17.0.2:4444.
07:00:24.419 INFO [LocalGridModel.setAvailability] - Switching node 218787d9-1433-40fc-a6c2-792e573c1a68 (uri: http://172.17.0.2:4444) from DOWN to UP
07:00:24.652 INFO [Standalone.execute] - Started Selenium Standalone 4.0.0-rc-1 (revision 23ece4f646): http://172.17.0.2:4444
```

Selenium Serverが入るモチベーション

ドライバに対応していないブラウザを操作するにはSelenium Serverを利用します。

Selenium ServerはJavaで書かれたサーバーで、クライアントとドライバの中継サーバーとして振る舞うので、クライアントライブラリがドライバの管理をする必要がなくなります。

=== Selenium Grid

> Selenium Grid は Chrome, Firefox, IE などの複数種類のブラウザや複数バージョンのブラウザをプールしておき、Hub を経由してそれらの複数のブラウザで並行して同じテストを実行することができるというすごい仕組みです。

https://qiita.com/Chanmoro/items/9a3c86bb465c1cce738a

Gridの場合はGrid HubとGrid Node

公式の解説はこちら

https://www.selenium.dev/documentation/en/grid/grid_4/advanced_features/observability/

=== Try selenium written in python

```python
from selenium import webdriver


options = webdriver.ChromeOptions()
options.add_argument('--headless')

driver = webdriver.Remote(
    command_executor='http://localhost:4444/wd/hub',
    desired_capabilities=options.to_capabilities(),
    options=options,
)

driver.get('https://www.google.com/')
print(driver.current_url)

driver.quit()
```

- Codeのオプション解説

Create a new driver that will issue commands using the wire protocol by selenium/py code.

=== Driver接続時のオプション解説

```python
driver = webdriver.Remote(
    command_executor='http://localhost:4444/wd/hub',
    desired_capabilities=options.to_capabilities(),
    options=options,
)
```

The options are as follows

```python
         - command_executor - Either a string representing URL of the remote server or a custom
             remote_connection.RemoteConnection object. Defaults to 'http://127.0.0.1:4444/wd/hub'.
         - desired_capabilities - A dictionary of capabilities to request when
             starting the browser session. Required parameter.
         - browser_profile - A selenium.webdriver.firefox.firefox_profile.FirefoxProfile object.
             Only used if Firefox is requested. Optional.
         - proxy - A selenium.webdriver.common.proxy.Proxy object. The browser session will
             be started with given proxy settings, if possible. Optional.
         - keep_alive - Whether to configure remote_connection.RemoteConnection to use
             HTTP keep-alive. Defaults to True.
         - file_detector - Pass custom file detector object during instantiation. If None,
             then default LocalFileDetector() will be used.
         - options - instance of a driver options.Options class
```

- command_executor に Selenium ServerのURLを設定する
- proxyとはなにか、constructorで渡すのはdeprecatedになっているよ

https://qiita.com/Chanmoro/items/9a3c86bb465c1cce738a

=== Proxy

WebDriverのHttpProxyとしてデザインする場合

https://www.selenium.dev/documentation/en/webdriver/http_proxies/

=== commandとはなにか？

```
selenium-proxy-server_1  | request method: 'GET', body: ''
selenium-proxy-server_1  | response status: '404', body: '{
selenium-proxy-server_1  |   "value": {
selenium-proxy-server_1  |     "error": "unknown command",
selenium-proxy-server_1  |     "message": "Unable to find handler for (GET) \u002fwd\u002fhub",
selenium-proxy-server_1  |     "stacktrace": ""
selenium-proxy-server_1  |   }
selenium-proxy-server_1  | }'
```

commandがURIに入ってくるAPI Interfaceになっている気配がある

commandはURIパスについてくる。例えばセッションの場合は以下となる

```
http://localhost:4444/wd/hub/session
```

Selenium Serverのログ

```
$ docker log 473fe763ab06
07:02:08.679 INFO [LocalDistributor.newSession] - Session request received by the distributor:
 [Capabilities {browserName: chrome, goog:chromeOptions: {args: [--headless], extensions: []}, platform: ANY, version: }, Capabilities {browserName: chrome, goog:chromeOptions: {args: [--headless], extensions: []}}, Capabilities {browserName: chrome, goog:chromeOptions: {args: [--headless], extensions: []}, platformName: any}]
Starting ChromeDriver 91.0.4472.101 (af52a90bf87030dd1523486a1cd3ae25c5d76c9b-refs/branch-heads/4472@{#1462}) on port 1929
Only local connections are allowed.
Please see https://chromedriver.chromium.org/security-considerations for suggestions on keeping ChromeDriver safe.
ChromeDriver was started successfully.
[1624690928.726][SEVERE]: bind() failed: Cannot assign requested address (99)
07:02:09.258 INFO [ProtocolHandshake.createSession] - Detected dialect: W3C
07:02:09.287 INFO [LocalDistributor.newSession] - Session created by the distributor. Id: 2dcf9ba78fea5a08fee58700486e8f92, Caps: Capabilities {acceptInsecureCerts: false, browserName: chrome, browserVersion: 91.0.4472.114, chrome: {chromedriverVersion: 91.0.4472.101 (af52a90bf870..., userDataDir: /tmp/.com.google.Chrome.4h81bg}, goog:chromeOptions: {debuggerAddress: localhost:44475}, networkConnectionEnabled: false, pageLoadStrategy: normal, platformName: ANY, proxy: Proxy(), se:cdp: ws://172.17.0.2:4444/sessio..., se:cdpVersion: 91.0.4472.114, se:vnc: ws://172.17.0.2:4444/sessio..., se:vncEnabled: true, se:vncLocalAddress: ws://localhost:7900/websockify, setWindowRect: true, strictFileInteractability: false, timeouts: {implicit: 0, pageLoad: 300000, script: 30000}, unhandledPromptBehavior: dismiss and notify, webauthn:extension:largeBlob: true, webauthn:virtualAuthenticators: true}
07:02:10.230 INFO [LocalSessionMap.lambda$new$0] - Deleted session from local session map, Id: 2dcf9ba78fea5a08fee58700486e8f92
```

- ProtocolHandshake とはなにをしているのか
- Sessionとはなにを表しているのか

更に詳細

- Selenium Serverの中身、どういうコードでこのログは出るのか

=== Selenium Server Docker image

https://gihyo.jp/admin/serial/01/ubuntu-recipe/0662?page=2

=== Proxy Server

Proxy実装にあたり参考になりそうなload balancer実装

[https://github.com/aerokube/ggr](https://github.com/aerokube/ggr)

=== APIでリクエストする

- docker-composeでselenium serverを立ち上げる

- Sessionを立ち上げる場合は次のようなAPIリクエストがSelenium Serverに対して行われる

```
$ curl -X POST \
       -H "Content-Type: application/json" \
       -d '{"capabilities": {"firstMatch": [{}], "alwaysMatch": {"browserName": "chrome", "platformName": "any", "goog:chromeOptions": {"extensions": [], "args": ["--headless"]}}}, "desiredCapabilities": {"browserName": "chrome", "version": "", "platform": "ANY", "goog:chromeOptions": {"extensions": [], "args": ["--headless"]}}}' \
       http://localhost:4444/wd/hub/session

{
  "value": {
    "sessionId": "68da4c4d881321a51c6e354f466d6715",
    "capabilities": {
      "acceptInsecureCerts": false,
      "browserName": "chrome",
      "browserVersion": "91.0.4472.114",
      "chrome": {
        "chromedriverVersion": "91.0.4472.101 (af52a90bf87030dd1523486a1cd3ae25c5d76c9b-refs\u002fbranch-heads\u002f4472@{#1462})",
        "userDataDir": "\u002ftmp\u002f.com.google.Chrome.Bcs4AN"
      },
      "goog:chromeOptions": {
        "debuggerAddress": "localhost:33431"
      },
      "networkConnectionEnabled": false,
      "pageLoadStrategy": "normal",
      "platformName": "linux",
      "proxy": {
      },
      "se:cdp": "ws:\u002f\u002f172.23.0.2:4444\u002fsession\u002f68da4c4d881321a51c6e354f466d6715\u002fse\u002fcdp",
      "se:cdpVersion": "91.0.4472.114",
      "se:vnc": "ws:\u002f\u002f172.23.0.2:4444\u002fsession\u002f68da4c4d881321a51c6e354f466d6715\u002fse\u002fvnc",
      "se:vncEnabled": true,
      "se:vncLocalAddress": "ws:\u002f\u002flocalhost:7900\u002fwebsockify",
      "setWindowRect": true,
      "strictFileInteractability": false,
      "timeouts": {
        "implicit": 0,
        "pageLoad": 300000,
        "script": 30000
      },
      "unhandledPromptBehavior": "dismiss and notify",
      "webauthn:extension:largeBlob": true,
      "webauthn:virtualAuthenticators": true
    }
  }
}
```

作成されたSessionはsessionID`68da4c4d881321a51c6e354f466d6715`で識別できます。
以降このsessionIDをURLのパスに入れることで当該セッションでの操作をWebDriverへリクエストしていきます。

```
$ curl -X POST \
       -H "Content-Type: application/json" \
       -d '{"url": "https://www.google.com/"}' \
       http://localhost:4444/wd/hub/session/779f6b972ea5f3c3810b78191e95b3af/url

{"value":null}
```

なお、セッションは自動的にSelenium Server側で削除される

```
selenium-server_1        | 21:38:44.244 INFO [LocalSessionMap.lambda$new$0] - Deleted session from local session map, Id: 779f6b972ea5f3c3810b78191e95b3af
```

todo: selenium server内部での話なのか、その先なのかは要確認
