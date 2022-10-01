#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc!=2) {
		cout << "Usage:" << endl << ".\\FakeRansom.exe <directory-to-encrypt>" << endl;
		return 1;
	}
	cout << "FakeRansom encrypts .txt files in specified directory (non-recursive)." << endl;

	char path[MAX_PATH];
	strcpy_s(path, argv[1]);
	strcat_s(path, "\\*");

	char buf[MAX_PATH*2];
	snprintf(buf, MAX_PATH*2, "Encrypting '%s'.\nAre you sure you want to continue?", path);
	BOOL res = MessageBoxA(NULL, buf, "Confirmation", MB_YESNO);
	if(res == IDNO) {
		cout << "exited without encryption" << endl;
		return 0;
	}

	res = MessageBoxA(NULL, "Are you really sure?", "Final Confirmation", MB_YESNO);
	if(res == IDNO) {
		cout << "exited without encryption" << endl;
		return 0;
	}

	HANDLE hFind;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFileA(path, &ffd);
	if(hFind!=INVALID_HANDLE_VALUE) {
		do {
			if((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				if(strstr(ffd.cFileName, ".txt")) {
					// could be replaced with OpenFile
					char filepath[MAX_PATH];
					strcpy_s(filepath, argv[1]);
					strcat_s(filepath, "\\");
					strcat_s(filepath, ffd.cFileName);

					HANDLE hFile;
					DWORD writesize;
					char buf[] = "\nencrypted\n";
					hFile = CreateFileA(filepath, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if(hFile!=INVALID_HANDLE_VALUE) {
						SetFilePointer(hFile, 0, NULL, FILE_END);
						WriteFile(hFile, buf, strlen(buf), &writesize, NULL);
						cout << filepath << " encrypted" << endl;
					}
				}
			}
		}
		while(FindNextFile(hFind, &ffd));
	}
	FindClose(hFind);

	return 0;
}
