#pragma once

using namespace System;
using namespace System::Collections::Generic;

typedef List<String^> StrList;

public ref class ApiDict {
public:
	Dictionary<String^, List<String^>^>^ apiDict;
	ApiDict() {
		apiDict = gcnew Dictionary<String^, List<String^>^>();
		//�`�F�b�N�{�b�N�X�̍\���ɂ���u�\�����閼�́v�Ƃ���ɑΉ�����WindowsAPI�������`���Œǉ�����
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

		//�t�@�C������
		buf100->Add("MoveFileW");
		buf100->Add("MoveFileExA");
		buf100->Add("MoveFileExW");
		apiDict->Add("�t�@�C�����ύX", buf100);

		buf2->Add("DeleteFileW");
		buf2->Add("DeleteFileA");
		apiDict->Add("�t�@�C���폜", buf2);

		buf4->Add("WriteFile");
		apiDict->Add("�t�@�C����������", buf4);

		//�C���^�[�l�b�g�ڑ�
		buf5->Add("inet_pton");
		apiDict->Add("WinSock", buf5);

		buf6->Add("InternetOpenUrlA");
		apiDict->Add("WinInet", buf6);

		//���W�X�g������
		buf7->Add("RegCreateKeyExA");
		buf7->Add("RegCreateKeyExW");
		apiDict->Add("RUN���W�X�g���ւ̓o�^", buf7);


		//Windows�T�[�r�X����
		buf9->Add("CreateServiceA");
		apiDict->Add("Windows�T�[�r�X����", buf9);

		//�v���Z�X����
		buf10->Add("CreateProcessA");
		apiDict->Add("�q�v���Z�X�̐���", buf10);

		//�}���E�F�A���ۂ�����
		buf11->Add("IsDebuggerPresent");
		apiDict->Add("�f�o�b�K���m", buf11);

		buf12->Add("CryptDecrypt");
		apiDict->Add("�Í�������", buf12);

		buf13->Add("SetFileAttributesA");
		buf13->Add("SetFileAttributesW");
		apiDict->Add("�������g�̉B���t�@�C����", buf13);

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
