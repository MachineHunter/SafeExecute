#include <windows.h>

int main(void) {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);

	WCHAR path[] = L".\\hello.exe";
	CreateProcessW(NULL, (LPWSTR)path, NULL, NULL, 0, 0, NULL, NULL, &si, &pi);
	return 0;
}
