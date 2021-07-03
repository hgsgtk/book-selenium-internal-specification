
= Selenium

https://www.codegrid.net/articles/2014-selenium-1/

BrowserStackによる解説

かんたんな解説になっていてよい

https://www.browserstack.com/guide/selenium-webdriver-tutorial

Selenium Full CourceについてのYouTubeチャンネルがない。

https://www.bestproxyreviews.com/selenium-proxy/

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

https://www.browserstack.com/guide/selenium-webdriver-tutorial

BrowserStack での解説記事では使っているということになりそう

> JSON is an acronym for JavaScript Object Notation. It is an open standard that provides a transport mechanism for transferring data between client and server on the web. It provides support for various data structures like arrays and objects which makes it easier to read and write data from JSON.


JSON Wire Protocol だけをめっちゃ解説するっていうのもあり

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

日本語ドキュメントはこちら https://www.selenium.dev/documentation/ja/webdriver/http_proxies/

> プロキシサーバーは、クライアントとサーバー間の要求の仲介役として機能します。 簡単に言えば、トラフィックはプロキシサーバーを経由して、要求したアドレスに戻り、戻ってきます。

- ネットワークトラフィックをキャプチャする
- ウェブサイトによって行われた模擬バックエンドを呼び出す
- 複雑なネットワークトポロジーまたは厳格な企業の制限/ポリシーの下で、必要なWebサイトにアクセスします。

ということで、よき

BrowserStackの解説が以下である。

https://www.browserstack.com/guide/set-proxy-in-selenium

> A proxy is an intermediary between client requests and server responses. Proxies are primarily used to ensure privacy and encapsulation between numerous interactive systems.

Proxy serverの使い方についてはいくつか記事があるが、使い方については全然記事がないな。
ここはニッチな需要がありそう。

https://qiita.com/skimhiro/items/de501f45607d6a09cde5

参考事例となりそうなproxy実装

https://github.com/lightbody/browsermob-proxy

```
$ ./browsermob-proxy -port 8080
```

こういうインタフェースね

https://github.com/lightbody/browsermob-proxy/releases ここから最新の実行binをダウンロードする

Javaがない場合は素直にJavaのページからinstallすればよい



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

== Driverバージョン違い問題

https://chromedriver.chromium.org/downloads

Chrome driver installしようね
https://chromedriver.storage.googleapis.com/index.html?path=91.0.4472.101/

`brew install chromedriver` でも可能

== Selenium Client Driverを読む

https://github.com/SeleniumHQ/selenium/blob/b300c358f65f33c0cf43177316f433601c027bdb/py/README.rst#L2

読んでみましょう、Pythonで読んでみますよ

READMEにあるとおりこちらでPython的なAPI仕様が見れるよ https://www.selenium.dev/selenium/docs/api/py/webdriver_chromium/selenium.webdriver.chromium.options.html#module-selenium.webdriver.chromium.options

たぶんここがClient DriverとしてのProxy実装だね

https://github.com/SeleniumHQ/selenium/blob/0e0194b0e52a34e7df4b841f1ed74506beea5c3e/py/selenium/webdriver/common/proxy.py#L62

httpProxyだけなのかな？って思ってたら結構あるのね

```python
    ftpProxy = ''
    httpProxy = ''
    noProxy = ''
    proxyAutoconfigUrl = ''
    sslProxy = ''
    socksProxy = ''
```

動作コードだけ見てもチョットわからないのでテストコードを見てみよう

https://github.com/SeleniumHQ/selenium/blob/b300c358f65f33c0cf43177316f433601c027bdb/py/test/selenium/webdriver/common/proxy_tests.py#L23

```python
MANUAL_PROXY = {
    'httpProxy': 'some.url:1234',
    'ftpProxy': 'ftp.proxy',
    'noProxy': 'localhost, foo.localhost',
    'sslProxy': 'ssl.proxy:1234',
    'socksProxy': 'socks.proxy:65555',
    'socksUsername': 'test',
    'socksPassword': 'test',
    'socksVersion': 5,
}
```

firefoxの場合はProxy自体をsetするところはここよ https://github.com/SeleniumHQ/selenium/blob/a22d0fd220abf69e7ad32100f6f60a426dfba9c6/py/selenium/webdriver/firefox/options.py#L100

ChromeDriverはChrniumDriverをinheritしてる

さて、よくわからんから、うまくproxyが機能しなっかったときのこのエラーをみてみようか

```
$ python go_google_directly_webdriver.py
Traceback (most recent call last):
  File "go_google_directly_webdriver.py", line 10, in <module>
    driver.get('https://www.google.com/')
  File "/Users/kazukihigashiguchi/.pyenv/versions/3.8.8/lib/python3.8/site-packages/selenium/webdriver/remote/webdriver.py", line 333, in get
    self.execute(Command.GET, {'url': url})
  File "/Users/kazukihigashiguchi/.pyenv/versions/3.8.8/lib/python3.8/site-packages/selenium/webdriver/remote/webdriver.py", line 321, in execute
    self.error_handler.check_response(response)
  File "/Users/kazukihigashiguchi/.pyenv/versions/3.8.8/lib/python3.8/site-packages/selenium/webdriver/remote/errorhandler.py", line 242, in check_response
    raise exception_class(message, screen, stacktrace)
selenium.common.exceptions.WebDriverException: Message: unknown error: net::ERR_TUNNEL_CONNECTION_FAILED
  (Session info: chrome=91.0.4472.114)
 ```

共通で発行される基底例外

https://github.com/SeleniumHQ/selenium/blob/f75343f8b74bb90a760560659168ba7c1fc071aa/py/selenium/common/exceptions.py#L25

`webdriver.py", line 321` にヒントがあるので見に行こうね

`def start_session(self, capabilities: dict, browser_profile=None) -> None:` である :)

start_sessionとはあの /session ですね、わかりやすいですねぇ

`def execute(self, driver_command: str, params: dict = None) -> dict:` でdriver commandを送るんですねぇ

https://github.com/SeleniumHQ/selenium/blob/e46dba531896f67bdb93ba8d9e1d64f8b6b75b6f/py/selenium/webdriver/remote/webdriver.py#L380

ちょっと場所は違うけどおそらくこのエラーレスポンスハンドリングをしているのかな https://github.com/SeleniumHQ/selenium/blob/e46dba531896f67bdb93ba8d9e1d64f8b6b75b6f/py/selenium/webdriver/remote/webdriver.py#L400

statusがどれでもないときは https://github.com/SeleniumHQ/selenium/blob/916168f403dded05f878fe189d68c0f9152335c9/py/selenium/webdriver/remote/errorhandler.py#L196 のようにエラーが返る

ってことは適当にstatusを返せばエラー時のフィードバックが送れるんかな？

やってみたけどかわらへんわ、はは

```
selenium.common.exceptions.WebDriverException: Message: unknown error: net::ERR_TUNNEL_CONNECTION_FAILED
```

どこだろうね

なかのレスポンスを見た、そもそもってことね

```
        print(response)
```

```
{'status': 500, 'value': '{"value":{"error":"unknown error","message":"unknown error: net::ERR_TUNNEL_CONNECTION_FAILED\\n  (Session info: headless chrome=91.0.4472.114)","stacktrace":"0   chromedriver                        0x00000001050c2649 chromedriver + 2741833\\n1   chromedriver                        0x0000000105778fb3 chromedriver + 9781171\\n2   chromedriver                        0x0000000104e4f308 chromedriver + 172808\\n3   chromedriver                        0x0000000104e49423 chromedriver + 148515\\n4   chromedriver                        0x0000000104e3b7fd chromedriver + 92157\\n5   chromedriver                        0x0000000104e3c5ba chromedriver + 95674\\n6   chromedriver                        0x0000000104e3ba75 chromedriver + 92789\\n7   chromedriver                        0x0000000104e3b121 chromedriver + 90401\\n8   chromedriver                        0x0000000104e3a12c chromedriver + 86316\\n9   chromedriver                        0x0000000104e3a423 chromedriver + 87075\\n10  chromedriver                        0x0000000104e50d1e chromedriver + 179486\\n11  chromedriver                        0x0000000104eb2671 chromedriver + 579185\\n12  chromedriver                        0x0000000104ea0552 chromedriver + 505170\\n13  chromedriver                        0x0000000104eb1e94 chromedriver + 577172\\n14  chromedriver                        0x0000000104ea0863 chromedriver + 505955\\n15  chromedriver                        0x0000000104e76ef1 chromedriver + 335601\\n16  chromedriver                        0x0000000104e78125 chromedriver + 340261\\n17  chromedriver                        0x000000010508975c chromedriver + 2508636\\n18  chromedriver                        0x000000010509c686 chromedriver + 2586246\\n19  chromedriver                        0x000000010506eb51 chromedriver + 2399057\\n20  chromedriver                        0x000000010509da5f chromedriver + 2591327\\n21  chromedriver                        0x000000010507f6ec chromedriver + 2467564\\n22  chromedriver                        0x00000001050b72d8 chromedriver + 2695896\\n23  chromedriver                        0x00000001050b746b chromedriver + 2696299\\n24  chromedriver                        0x00000001050c7558 chromedriver + 2762072\\n25  libsystem_pthread.dylib             0x00007fff2050a8fc _pthread_start + 224\\n26  libsystem_pthread.dylib             0x00007fff20506443 thread_start + 15\\n"}}'}
```

ん？これはどこからきているかというと？

WebDriverのinitializeは完了してるので、ここまでは問題ない（実際だからこそbrowserが立ち上がっている側面がある）

```python
driver.get('https://www.google.com/')
```

ここでこけてるようだったわ

=== session開始時のリクエストはproxyには飛ばないの？

TBD proxyがどこまで関与する仕様なのかを要調査

一個目のリクエストに対するレスポンス

```json
{'value': {'capabilities': {'acceptInsecureCerts': False, 'browserName': 'chrome', 'browserVersion': '91.0.4472.114', 'chrome': {'chromedriverVersion': '91.0.4472.101 (af52a90bf87030dd1523486a1cd3ae25c5d76c9b-refs/branch-heads/4472@{#1462})', 'userDataDir': '/var/folders/t5/3p4crbvn2476w3xbrmstrmtr0000gn/T/.com.google.Chrome.yiB7kH'}, 'goog:chromeOptions': {'debuggerAddress': 'localhost:52367'}, 'networkConnectionEnabled': False, 'pageLoadStrategy': 'normal', 'platformName': 'mac os x', 'proxy': {}, 'setWindowRect': True, 'strictFileInteractability': False, 'timeouts': {'implicit': 0, 'pageLoad': 300000, 'script': 30000}, 'unhandledPromptBehavior': 'dismiss and notify', 'webauthn:extension:largeBlob': True, 'webauthn:virtualAuthenticators': True}, 'sessionId': '6cfb3a2b62a563fd1f6e0353bf287bd6'}}
```

これはセッション開始する子だわね

ふたつめで500がでている

```
{'status': 500, 'value': '{"value":{"error":"unknown error","message":"unknown error: net::ERR_TUNNEL_CONNECTION_FAILED\\n  (Session info: headless chrome=91.0.4472.114)","stacktrace":"0   chromedriver                        0x000000010fbdc649 chromedriver + 2741833\\n1   chromedriver                        0x0000000110292fb3 chromedriver + 9781171\\n2   chromedriver                        0x000000010f969308 chromedriver + 172808\\n3   chromedriver                        0x000000010f963423 chromedriver + 148515\\n4   chromedriver                        0x000000010f9557fd chromedriver + 92157\\n5   chromedriver                        0x000000010f9565ba chromedriver + 95674\\n6   chromedriver                        0x000000010f955a75 chromedriver + 92789\\n7   chromedriver                        0x000000010f955121 chromedriver + 90401\\n8   chromedriver                        0x000000010f95412c chromedriver + 86316\\n9   chromedriver                        0x000000010f954423 chromedriver + 87075\\n10  chromedriver                        0x000000010f96ad1e chromedriver + 179486\\n11  chromedriver                        0x000000010f9cc671 chromedriver + 579185\\n12  chromedriver                        0x000000010f9ba552 chromedriver + 505170\\n13  chromedriver                        0x000000010f9cbe94 chromedriver + 577172\\n14  chromedriver                        0x000000010f9ba863 chromedriver + 505955\\n15  chromedriver                        0x000000010f990ef1 chromedriver + 335601\\n16  chromedriver                        0x000000010f992125 chromedriver + 340261\\n17  chromedriver                        0x000000010fba375c chromedriver + 2508636\\n18  chromedriver                        0x000000010fbb6686 chromedriver + 2586246\\n19  chromedriver                        0x000000010fb88b51 chromedriver + 2399057\\n20  chromedriver                        0x000000010fbb7a5f chromedriver + 2591327\\n21  chromedriver                        0x000000010fb996ec chromedriver + 2467564\\n22  chromedriver                        0x000000010fbd12d8 chromedriver + 2695896\\n23  chromedriver                        0x000000010fbd146b chromedriver + 2696299\\n24  chromedriver                        0x000000010fbe1558 chromedriver + 2762072\\n25  libsystem_pthread.dylib             0x00007fff2050a8fc _pthread_start + 224\\n26  libsystem_pthread.dylib             0x00007fff20506443 thread_start + 15\\n"}}'}
```

Proxy serverを介さないとこうなるべきっていう話らしいよ

```
$ python go_google_directly_webdriver.py
{'value': {'capabilities': {'acceptInsecureCerts': False, 'browserName': 'chrome', 'browserVersion': '91.0.4472.114', 'chrome': {'chromedriverVersion': '91.0.4472.101 (af52a90bf87030dd1523486a1cd3ae25c5d76c9b-refs/branch-heads/4472@{#1462})', 'userDataDir': '/var/folders/t5/3p4crbvn2476w3xbrmstrmtr0000gn/T/.com.google.Chrome.ojvdXQ'}, 'goog:chromeOptions': {'debuggerAddress': 'localhost:52393'}, 'networkConnectionEnabled': False, 'pageLoadStrategy': 'normal', 'platformName': 'mac os x', 'proxy': {}, 'setWindowRect': True, 'strictFileInteractability': False, 'timeouts': {'implicit': 0, 'pageLoad': 300000, 'script': 30000}, 'unhandledPromptBehavior': 'dismiss and notify', 'webauthn:extension:largeBlob': True, 'webauthn:virtualAuthenticators': True}, 'sessionId': '71712c2a85ab882be63ac106a9c02fab'}}
{'value': None}
{'value': 'https://www.google.com/'}
https://www.google.com/
{'value': None}
```

client -> proxy -> driver へと渡っていないのかな、なんだかよくわからん感じでおわったみたいなことに
もうちょい proxy にリクエストするのはどういう感じなのかを確認しよう

Python codeのdriverからリクエストするときのmethod, url, bodyをとってみた。

```python
        parsed_url = parse.urlparse(url)
        headers = self.get_remote_connection_headers(parsed_url, self.keep_alive)
        resp = None
        if body and method != 'POST' and method != 'PUT':
            body = None

        if self.keep_alive:
            print("method: {}, url: {}, body: {}", method, url, body)
            resp = self._conn.request(method, url, body=body, headers=headers)

            statuscode = resp.status
        else:
            http = urllib3.PoolManager(timeout=self._timeout)
            resp = http.request(method, url, body=body, headers=headers)
```

そしたらこう

```
method: {}, url: {}, body: {} POST http://127.0.0.1:52540/session {"capabilities": {"firstMatch": [{}], "alwaysMatch": {"browserName": "chrome", "platformName": "any", "goog:chromeOptions": {"extensions": [], "args": ["--proxy-server=127.0.0.1:8080", "--headless"]}}}, "desiredCapabilities": {"browserName": "chrome", "version": "", "platform": "ANY", "goog:chromeOptions": {"extensions": [], "args": ["--proxy-server=127.0.0.1:8080", "--headless"]}}}
method: {}, url: {}, body: {} POST http://127.0.0.1:52540/session/525377f9630dc8c6254dc82d72abcbaa/url {"url": "https://www.google.com/"}
```

これあれか、proxyが意識するのはwebdriverだけで、webdriverに対して「ここがproxyです」っていうのをargsでwebdriver指定時に共有するっていうだけの設計なのか
clientはぶっちゃけproxyが実際どういう責務を持っている子なのかはよくしらない。

`"args": ["--proxy-server=127.0.0.1:8080", "--headless"]}`

次知るべきはproxyを渡されたwebdriverがどのような振る舞いをしてproxyと通信するのか、どういったプロトコルがそこにあるのかについて確認するというのが必要

=== WebDriverの振る舞い、proxyとの通信方法

TODO: WebDriverの実装とか仕様がどこで見れるのかを確認する

=== リクエスト時のHTTP Header

```
{'Accept': 'application/json', 'Content-Type': 'application/json;charset=UTF-8', 'User-Agent': 'selenium/3.141.0 (python mac)', 'Connection': 'keep-alive'}
{'Accept': 'application/json', 'Content-Type': 'application/json;charset=UTF-8', 'User-Agent': 'selenium/3.141.0 (python mac)', 'Connection': 'keep-alive'}
{'Accept': 'application/json', 'Content-Type': 'application/json;charset=UTF-8', 'User-Agent': 'selenium/3.141.0 (python mac)', 'Connection': 'keep-alive'}
https://www.google.com/
{'Accept': 'application/json', 'Content-Type': 'application/json;charset=UTF-8', 'User-Agent': 'selenium/3.141.0 (python mac)', 'Connection': 'keep-alive'}
```

Proxy設定があろうがなかろうが変わらない

=== Selenium repositoryの読み方

selenium clientが各言語で入ってるよ

=== driver command一覧

=== response

status一覧

これめっちゃ極めたら自分のselenium client作れるようになるな
JSON Wire Protocolを理解して己のselenium clientを作ろう
それをGoでやってもいいかもしれないね
Rustでも可
