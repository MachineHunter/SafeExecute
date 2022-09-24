#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
	char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);
	strcat_s(path, "\\*");

	HANDLE hFind;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFileA(path, &ffd);
	if(hFind!=INVALID_HANDLE_VALUE) {
		do {
			if((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				if(strstr(ffd.cFileName, ".exe"))
					cout << ffd.cFileName << endl;
			}
		}
		while(FindNextFile(hFind, &ffd));
	}
	FindClose(hFind);
	return 0;
}
