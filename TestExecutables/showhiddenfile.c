#include <windows.h>

int main(void) {
	SetFileAttributesA(".\\hiddenfile.exe", FILE_ATTRIBUTE_NORMAL);
	return 0;
}
