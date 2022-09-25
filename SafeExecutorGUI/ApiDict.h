#pragma once

using namespace System;
using namespace System::Collections::Generic;

typedef List<String^> StrList;

public ref class ApiDict {
public:
	Dictionary<String^, List<String^>^>^ apiDict;
	ApiDict() {
		apiDict = gcnew Dictionary<String^, List<String^>^>();
		//チェックボックスの構成にある「表示する名称」とそれに対応するWindowsAPIを辞書形式で追加する
		buf2 = gcnew StrList();
		buf4 = gcnew StrList();
		buf5 = gcnew StrList();
		buf6 = gcnew StrList();
		buf7 = gcnew StrList();
		buf9 = gcnew StrList();
		buf10 = gcnew StrList();
		buf100 = gcnew StrList();
		buf11 = gcnew StrList();
		buf12 = gcnew StrList();
		buf13 = gcnew StrList();

		//ファイル操作
		buf100->Add("MoveFileW");
		buf100->Add("MoveFileExA");
		buf100->Add("MoveFileExW");
		apiDict->Add("ファイル名変更", buf100);

		buf2->Add("DeleteFileW");
		buf2->Add("DeleteFileA");
		apiDict->Add("ファイル削除", buf2);

		buf4->Add("WriteFile");
		apiDict->Add("ファイル書き込み", buf4);

		//インターネット接続
		buf5->Add("inet_pton");
		apiDict->Add("WinSock", buf5);

		buf6->Add("InternetOpenUrlA");
		apiDict->Add("WinInet", buf6);

		//レジストリ操作
		buf7->Add("RegCreateKeyExA");
		buf7->Add("RegCreateKeyExW");
		apiDict->Add("RUNレジストリへの登録", buf7);


		//Windowsサービス操作
		buf9->Add("CreateServiceA");
		apiDict->Add("Windowsサービス操作", buf9);

		//プロセス操作
		buf10->Add("CreateProcessA");
		apiDict->Add("子プロセスの生成", buf10);

		//マルウェアっぽい挙動
		buf11->Add("IsDebuggerPresent");
		apiDict->Add("デバッガ検知", buf11);

		buf12->Add("CryptDecrypt");
		apiDict->Add("暗号化処理", buf12);

		buf13->Add("SetFileAttributesA");
		buf13->Add("SetFileAttributesW");
		apiDict->Add("自分自身の隠しファイル化", buf13);

	}

private:
	StrList^ buf100;
	StrList^ buf2;
	StrList^ buf4;
	StrList^ buf5;
	StrList^ buf6;
	StrList^ buf7;
	StrList^ buf9;
	StrList^ buf10;
	StrList^ buf11;
	StrList^ buf12;
	StrList^ buf13;
	};
