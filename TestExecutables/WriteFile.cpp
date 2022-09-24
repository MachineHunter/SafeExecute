#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	HANDLE hFile;
	hFile = CreateFile(".\\test.txt", GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD writesize;
	char buf[] = "hello world";
	WriteFile(hFile, buf, strlen(buf), &writesize, NULL);

	CloseHandle(hFile);
	return 0;
}
