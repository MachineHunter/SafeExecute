#include "pch.h"
#include "prehook.h"

void PreHook(LPCSTR apiName) {
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
			char header[] = "timestamp,executable path,hooked windows api\n";
			WriteFile(hFile, header, strlen(header), &writesize, NULL);
		}

		SetFilePointer(hFile, 0, NULL, FILE_END);

		SYSTEMTIME time;
		GetLocalTime(&time);

		char buf[1000];
		snprintf(buf, 1000, "%04d/%02d/%02d %02d:%02d:%02d.%d,%s,%s\n",
			time.wYear, time.wMonth, time.wDay,
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
			processPath, apiName);

		WriteFile(hFile, buf, strlen(buf), &writesize, NULL);

		CloseHandle(hFile);
	}
	else {
		MessageBoxA(NULL, "Please execute SafeExecutor from project home directory", "PreHook Error", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}
}