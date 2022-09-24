#include <windows.h>

int main(void) {
	wchar_t filename[1000];
	GetModuleFileNameW(NULL, filename, 1000);
	SetFileAttributesW(filename, FILE_ATTRIBUTE_HIDDEN);
	return 0;
}
