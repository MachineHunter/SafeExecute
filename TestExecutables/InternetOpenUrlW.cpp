#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment( lib, "wininet" )

int main(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	HINTERNET hInternet;
	HINTERNET hFile;

	hInternet = InternetOpenW(L"Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	hFile = InternetOpenUrlW(hInternet, L"https://github.com/MachineHunter/SafeExecute", NULL, 0, INTERNET_FLAG_RELOAD, 0);

	while (1) {
		DWORD readsize = 1000;
		BOOL result;
		char buf[1000];

		result = InternetReadFile(hFile, buf, 1000, &readsize);

		if (result && (readsize == 0)) break;

		buf[readsize] = '\0';
		printf("%s", buf);
	}

	InternetCloseHandle(hFile);
	InternetCloseHandle(hInternet);

	return 0;
}