#include <windows.h>

int main(void) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);

	CreateProcessA(NULL, ".\\TestExecutables\\IsDebuggerPresent.exe", NULL, NULL, 0, 0, NULL, NULL, &si, &pi);
	CreateProcessA(NULL, ".\\TestExecutables\\CSP.exe", NULL, NULL, 0, 0, NULL, NULL, &si, &pi);
	
	if(IsDebuggerPresent())
		return 1;
	return 0;
}
