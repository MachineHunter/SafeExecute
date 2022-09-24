#include <windows.h>
#include <cstdio>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Sleep(300);
	MessageBoxA(NULL, TEXT("Hello World!"), TEXT("Test"), MB_YESNO | MB_ICONEXCLAMATION);
	return 0;
}
