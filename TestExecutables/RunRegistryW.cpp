// RegCreateKeyExW 用のテストコード
#include <Windows.h>

int main(void) {
	HKEY hKey;
	DWORD dwDisposition;

	RegCreateKeyExW(
		HKEY_CURRENT_USER,
		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE,
		NULL,
		&hKey,
		&dwDisposition);

	char exePath[MAX_PATH];
	GetModuleFileNameA(0, exePath, MAX_PATH);

	LSTATUS res = RegSetValueExA(
		hKey,
		"HogeHogeRegistry",
		0,
		REG_SZ,
		(BYTE*)exePath,
		MAX_PATH);

	if(res==ERROR_SUCCESS){
		MessageBoxA(NULL, "Check HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run by your regedit", "Success", MB_OK);
	}else
		MessageBoxA(NULL, "Failed RegSetValueExA", "Error", MB_OK);


	RegCloseKey(hKey);
	return 0;
}
