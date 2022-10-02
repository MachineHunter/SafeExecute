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
		buf11 = gcnew StrList();
		buf12 = gcnew StrList();
		buf13 = gcnew StrList();
		buf14 = gcnew StrList();
		buf21 = gcnew StrList();
		buf22 = gcnew StrList();
		buf23 = gcnew StrList();
		buf31 = gcnew StrList();
		buf41 = gcnew StrList();
		buf51 = gcnew StrList();
		buf52 = gcnew StrList();
		buf61 = gcnew StrList();
		buf62 = gcnew StrList();
		buf63 = gcnew StrList();
		buf64 = gcnew StrList();
		buf65 = gcnew StrList();
		buf66 = gcnew StrList();
		buf71 = gcnew StrList();

		//ファイル操作
		buf11->Add("MoveFileA");
		buf11->Add("MoveFileW");
		buf11->Add("MoveFileExA");
		buf11->Add("MoveFileExW");
		apiDict->Add("ファイル名変更", buf11);

		buf12->Add("DeleteFileW");
		buf12->Add("DeleteFileA");
		apiDict->Add("ファイル削除", buf12);

		buf13->Add("WriteFile");
		apiDict->Add("ファイル書き込み", buf13);

		buf14->Add("FindFirstFileA");
		buf14->Add("FindNextFileA");
		buf14->Add("FindFirstFileW");
		buf14->Add("FindNextFileW");
		apiDict->Add("ファイル走査", buf13);

		//インターネット接続
		buf21->Add("inet_pton");
		apiDict->Add("WinSock", buf21);

		buf22->Add("InternetOpenUrlA");
		buf22->Add("InternetOpenUrlW");
		apiDict->Add("WinInet", buf22);

		buf23->Add("URLDownloadToFileA");
		buf23->Add("URLDownloadToFileW");
		apiDict->Add("ファイルダウンロード", buf23);

		//レジストリ操作
		buf31->Add("RegCreateKeyExA");
		buf31->Add("RegCreateKeyExW");
		apiDict->Add("RUNレジストリへの登録", buf31);
		
		//Windowsサービス操作
		buf41->Add("CreateServiceA");
		buf41->Add("CreateServiceW");
		apiDict->Add("Windowsサービス操作", buf41);

		//プロセス操作
		buf51->Add("CreateProcessA");
		buf51->Add("CreateProcessW");
		apiDict->Add("子プロセスの生成", buf51);
		
		buf52->Add("OpenProcessToken");
		buf52->Add("AdjustTokenPrivileges");
		apiDict->Add("プロセスの権限変更", buf52);
		
		//マルウェアっぽい挙動
		buf61->Add("IsDebuggerPresent");
		apiDict->Add("デバッガ検知", buf61);

		buf62->Add("CryptDecrypt");
		apiDict->Add("暗号化処理", buf62);

		buf63->Add("SetFileAttributesA");
		buf63->Add("SetFileAttributesW");
		apiDict->Add("自分自身の隠しファイル化", buf63);
		
		buf64->Add("GetLocaleInfoA");
		buf64->Add("GetLocaleInfoW");
		buf64->Add("GetLocaleInfoEx");
		apiDict->Add("ロケール情報の取得", buf64);

		buf65->Add("CreateTimerQueueTimer");
		apiDict->Add("タイマーの使用", buf65);
		
		buf66->Add("SystemParametersInfoA");
		buf66->Add("SystemParametersInfoW");
		apiDict->Add("デスクトップ壁紙の変更", buf66);

		// 機能
		buf71->Add("CreateFileA");
		buf71->Add("CreateFileW");
		apiDict->Add("ファイルのバックアップ", buf71);
	}

private:
	StrList^ buf11;
	StrList^ buf12;
	StrList^ buf13;
	StrList^ buf14;
	StrList^ buf21;
	StrList^ buf22;
	StrList^ buf23;
	StrList^ buf31;
	StrList^ buf41;
	StrList^ buf51;
	StrList^ buf52;
	StrList^ buf61;
	StrList^ buf62;
	StrList^ buf63;
	StrList^ buf64;
	StrList^ buf65;
	StrList^ buf66;
	StrList^ buf71;
	};
