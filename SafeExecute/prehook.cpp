#include "pch.h"
#include "prehook.h"

void LogHookedApi(int argc, VCHAR argv) {
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\logs");

	if (PathFileExistsA(path)) {
		strcat_s(path, "\\log.csv");

		HANDLE hFile;
		DWORD writesize;
		if (PathFileExistsA(path)) {
			hFile = CreateFileA(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else {
			hFile = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			char header[] = "timestamp,executable path,hooked windows api,args\n";
			WriteFile(hFile, header, strlen(header), &writesize, NULL);
		}

		SetFilePointer(hFile, 0, NULL, FILE_END);

		SYSTEMTIME time;
		GetLocalTime(&time);

		char buf[1000];
		memset(buf, 0, 1000);
		snprintf(buf, 1000, "%04d/%02d/%02d %02d:%02d:%02d.%d,%s,%s",
			time.wYear, time.wMonth, time.wDay,
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
			processPath, argv[0]);
		for (int i = 1; i < argc; i++) {
			strcat_s(buf, ",");
			strcat_s(buf, argv[i]);
		}
		strcat_s(buf, "\n");

		WriteFile(hFile, buf, strlen(buf), &writesize, NULL);
		CloseHandle(hFile);
		return;
	}
	else {
		MessageBoxA(NULL, "Please execute SafeExecutor from project home directory", "PreHook Error", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}
}

void PreHook(int argc, ...) {
	va_list vl;
	va_start(vl, argc);
	VCHAR argv;
	for (int i = 0; i < argc; i++)
		argv.push_back(va_arg(vl, char*));

	LogHookedApi(argc, argv);

	switch (MODE)
	{
	case MODE_NORMAL:
		ExitProcess(1);
		break;
	case MODE_ERRORDISPLAY:
		char buf[256];
		snprintf(buf, 256, "Hooked %s", argv[0]);
		if (argc > 1) strcat_s(buf, "\nArguments:");
		for (int i = 1; i < argc; i++) {
			strcat_s(buf, "\n");
			char buf2[10];
			snprintf(buf2, 10, "%2d: ", i);
			strcat_s(buf, buf2);
			strcat_s(buf, argv[i]);
		}
		MessageBoxA(NULL, buf, "SafeExecute", MB_OK);
		ExitProcess(1);
		break;
	default:
		break;
	}
	return;
}