#pragma once

using namespace System;
using namespace System::Collections::Generic;

typedef List<String^> StrList;

public ref class ApiDict {
public:
	Dictionary<String^, List<String^>^>^ apiDict;
	ApiDict() {
		apiDict = gcnew Dictionary<String^, List<String^>^>();
		StrList^ buf;
		buf->Add("MoveFileW");
		apiDict->Add("ファイル名変更", buf);
		//buf->Clear();
		StrList^ buf2;
		buf2->Add("DeleteFileA");
		apiDict->Add("ファイル名削除", buf2);
		//apiDict->Add("ファイル名削除", StrList({"DeleteFileA","DeleteFileW"}));
		StrList^ buf3;
		buf3->Add("DeleteFileW");
		apiDict->Add("ファイル名削除", buf3);

		StrList^ buf4;
		buf4->Add("WriteFile");
		apiDict->Add("ファイル書き込み", buf4);

		StrList^ buf5;
		buf5->Add("WinSock");
		apiDict->Add("WinSock", buf5);

		StrList^ buf6;
		buf6->Add("WinInet");
		apiDict->Add("WinInet", buf6);

		StrList^ buf7;
		buf7->Add("WinInet");
		apiDict->Add("WinInet", buf7);

	}
};
