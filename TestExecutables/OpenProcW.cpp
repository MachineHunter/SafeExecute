#include <windows.h>

int main(void) {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);

	WCHAR path[] = L".\\TestExecutables\\IsDebuggerPresent.exe";
	WCHAR path2[] = L".\\TestExecutables\\CSP.exe";
	CreateProcessW(NULL, (LPWSTR)path, NULL, NULL, 0, 0, NULL, NULL, &si, &pi);
	CreateProcessW(NULL, (LPWSTR)path2, NULL, NULL, 0, 0, NULL, NULL, &si, &pi);
	
	if(IsDebuggerPresent())
		return 1;
	return 0;
}
