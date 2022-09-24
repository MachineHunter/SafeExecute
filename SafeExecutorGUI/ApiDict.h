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
		apiDict->Add("�t�@�C�����ύX", buf);
		//buf->Clear();
		StrList^ buf2;
		buf2->Add("DeleteFileA");
		apiDict->Add("�t�@�C�����폜", buf2);
		//apiDict->Add("�t�@�C�����폜", StrList({"DeleteFileA","DeleteFileW"}));
		StrList^ buf3;
		buf3->Add("DeleteFileW");
		apiDict->Add("�t�@�C�����폜", buf3);

		StrList^ buf4;
		buf4->Add("WriteFile");
		apiDict->Add("�t�@�C����������", buf4);

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
