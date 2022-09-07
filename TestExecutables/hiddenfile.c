#include <windows.h>

int main(void) {
	char filename[1000];
	GetModuleFileNameA(NULL, filename, 1000);
	SetFileAttributesA(filename, FILE_ATTRIBUTE_HIDDEN);
	return 0;
}
