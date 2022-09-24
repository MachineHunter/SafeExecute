# SafeExecute

## 概要
SafeExecuteは、実行ファイルの振舞いに制限を掛ける事により、安全に実行ファイルを実行させることができます。  
具体的には、SafeExecuteが提供する一覧の中から、ユーザーがチェックを入れた挙動を実行ファイルが行った場合、その実行ファイルの実行が停止されるという物です。  
多くのアンチウイルス製品は誤検知を回避するために、慎重にその実行ファイルの挙動が正当かどうかを確認します。
そのため、例えば明らかにネットワーク接続を必要としない物であるとユーザーが分かっている実行ファイルが、不審にもどこかのサーバーへ接続していた場合、ユーザーからしたら明らかに怪しいと分かりますが、アンチウイルス製品にとってはその接続だけの処理を見てこれが不審な挙動であるのかどうかを見極めるのは困難です。
このSafeExecuteは、実行ファイルのどのような挙動を禁止するかをユーザーが設定する事ができます。



## 実行方法
```sh
cd SafeExecutor/x64/Debug
./SafeExecutor.exe <path-to-SafeExecute.dll> <path-to-executables>
```


## 構成要素
* **SafeExecute**: 対象実行ファイルのWindowsAPIをフックし、挙動の監視及び悪性かどうかの判断とその場合の対応を行う
* **SafeExecutor**: 対象実行ファイルにSafeExecuteを組み込んで実行する
* **TestExecutables**: テスト用の実行ファイルとそのソースプログラム



## 仕組み
SafeExecuteは、対象の実行ファイルのWindowsAPIを監視する事により、この実行ファイルの挙動が怪しいかどうかを判断しています。  
この監視には、具体的にはAPIフックという手法を用いており、ここではAPIフックについて説明します。

SafeExecuteを用いて、以下のソースの実行ファイル(Hello.exe)を実行する場合を考えます。

```c++
#include <windows.h>
#include <cstdio>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MessageBoxA(NULL, "Hello World!", "Info", MB_YESNO);
	return 0;
}
```

これはメッセージボックスを表示するだけのプログラムです。  
本来この実行ファイルのMessageBoxAは、以下のようにしてuser32.dllから呼び出されます。

![](./img/callMessageBoxA.png)

ここでもし、SafeExecuteにて「メッセージボックスを表示する挙動」があった場合に実行を停止するという設定の下、この実行ファイルを実行した場合、
SafeExecuteはMessageBoxというWindowsAPIにAPIフックを掛けます。これにより、プログラムの実行は下図のように進みます。

![](./img/callHookedMessageBoxA.png)

つまり、関数呼び出しの間に、フック関数が入ります。フック関数にて、呼び出されたWindowsAPIの引数等を調査し、それらに応じて悪性かどうかを判断した後、
悪性と判断されれば実行停止(ExitProcess)、そうでなければ元のMessageBoxAの処理に戻すという事をしています。

この例では一つのWindowsAPIのみをフックしましたが、複数のWindowsAPIをフックし、その組み合わせにより悪性かどうかの判断をするという事も行う事ができます。
ユーザーは、禁止しない挙動をチェックする事で、SafeExecuteにどのWindowsAPIをフックさせるかを指定している事になります。
