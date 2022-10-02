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

		//�t�@�C������
		buf11->Add("MoveFileA");
		buf11->Add("MoveFileW");
		buf11->Add("MoveFileExA");
		buf11->Add("MoveFileExW");
		apiDict->Add("�t�@�C�����ύX", buf11);

		buf12->Add("DeleteFileW");
		buf12->Add("DeleteFileA");
		apiDict->Add("�t�@�C���폜", buf12);

		buf13->Add("WriteFile");
		apiDict->Add("�t�@�C����������", buf13);

		buf14->Add("FindFirstFileA");
		buf14->Add("FindNextFileA");
		buf14->Add("FindFirstFileW");
		buf14->Add("FindNextFileW");
		apiDict->Add("�t�@�C������", buf13);

		//�C���^�[�l�b�g�ڑ�
		buf21->Add("inet_pton");
		apiDict->Add("WinSock", buf21);

		buf22->Add("InternetOpenUrlA");
		buf22->Add("InternetOpenUrlW");
		apiDict->Add("WinInet", buf22);

		buf23->Add("URLDownloadToFileA");
		buf23->Add("URLDownloadToFileW");
		apiDict->Add("�t�@�C���_�E�����[�h", buf23);

		//���W�X�g������
		buf31->Add("RegCreateKeyExA");
		buf31->Add("RegCreateKeyExW");
		apiDict->Add("RUN���W�X�g���ւ̓o�^", buf31);
		
		//Windows�T�[�r�X����
		buf41->Add("CreateServiceA");
		buf41->Add("CreateServiceW");
		apiDict->Add("Windows�T�[�r�X����", buf41);

		//�v���Z�X����
		buf51->Add("CreateProcessA");
		buf51->Add("CreateProcessW");
		apiDict->Add("�q�v���Z�X�̐���", buf51);
		
		buf52->Add("OpenProcessToken");
		buf52->Add("AdjustTokenPrivileges");
		apiDict->Add("�v���Z�X�̌����ύX", buf52);
		
		//�}���E�F�A���ۂ�����
		buf61->Add("IsDebuggerPresent");
		apiDict->Add("�f�o�b�K���m", buf61);

		buf62->Add("CryptDecrypt");
		apiDict->Add("�Í�������", buf62);

		buf63->Add("SetFileAttributesA");
		buf63->Add("SetFileAttributesW");
		apiDict->Add("�������g�̉B���t�@�C����", buf63);
		
		buf64->Add("GetLocaleInfoA");
		buf64->Add("GetLocaleInfoW");
		buf64->Add("GetLocaleInfoEx");
		apiDict->Add("���P�[�����̎擾", buf64);

		buf65->Add("CreateTimerQueueTimer");
		apiDict->Add("�^�C�}�[�̎g�p", buf65);
		
		buf66->Add("SystemParametersInfoA");
		buf66->Add("SystemParametersInfoW");
		apiDict->Add("�f�X�N�g�b�v�ǎ��̕ύX", buf66);

		// �@�\
		buf71->Add("CreateFileA");
		buf71->Add("CreateFileW");
		apiDict->Add("�t�@�C���̃o�b�N�A�b�v", buf71);
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
