#include "pch.h"
#include "readmode.h"

DWORD MODE = MODE_NORMAL;

void ReadMode() {
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\rules");
	
	if (PathFileExistsA(path)) {
		strcat_s(path, "\\mode.txt");

		if (PathFileExistsA(path)) {
			char* mode = new char[1];
			ifstream f(path);
			f.read(mode, 1);
			MODE = atoi(mode);
		}
		else MessageBoxA(NULL, "Missing mode.txt in rules/ directory", "ReadMode Error", MB_OK | MB_ICONERROR);

	}
	else {
		MessageBoxA(NULL, "rules/ directory missing", "ReadMode Error", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}
}