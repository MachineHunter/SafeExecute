#include <Windows.h>
#include <stdio.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	if(__argc>1) {
		Sleep(200);
		MessageBoxA(NULL, lpCmdLine, "info", MB_OK);
	}
	else
		MessageBoxA(NULL, "you need args", "info", MB_OK);
	return 0;
}
