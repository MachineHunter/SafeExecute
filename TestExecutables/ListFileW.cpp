#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
	wchar_t path[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, path);
	wcscat(path, L"\\*");

	HANDLE hFind;
	WIN32_FIND_DATAW ffd;
	hFind = FindFirstFileW(path, &ffd);
	if(hFind!=INVALID_HANDLE_VALUE) {
		do {
			if((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				if(wcsstr(ffd.cFileName, L".exe"))
					wcout << ffd.cFileName << endl;
			}
		}
		while(FindNextFileW(hFind, &ffd));
	}
	FindClose(hFind);

	if (IsDebuggerPresent())
		return 1;
	return 0;
}
