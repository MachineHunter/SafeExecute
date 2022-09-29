#include <windows.h>
#include <stdio.h>
int main() {

	TOKEN_PRIVILEGES tkp;
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		MessageBoxA(NULL, "OpenProcessToken failed!", "debug", MB_OK); //Failed OpenProcessToken
	}
	MessageBoxA(NULL, "OpenProcessToken", "debug", MB_OK);

    // reference: https://s-kita.hatenablog.com/entry/20110404/1301921117
    DWORD dwLength;
    //HANDLE hToken;
    PTOKEN_USER pTokenUser;
    char szAccountName[256];
    DWORD dwAccountNameSize;
    char szDomainName[256];
    DWORD dwDomainNameSize;
    SID_NAME_USE snu;

    GetTokenInformation(hToken, TokenUser, NULL, 0, &dwLength);
    pTokenUser = (PTOKEN_USER)LocalAlloc(LPTR, dwLength);
    if (pTokenUser == NULL) {
        CloseHandle(hToken);
        return 1;
    }

    //2.GetTokenInformation関数で、トークン情報を取得する
    GetTokenInformation(hToken, TokenUser, pTokenUser, dwLength, &dwLength);


    dwAccountNameSize = sizeof(szAccountName) / sizeof(szAccountName[0]);
    dwDomainNameSize = sizeof(szDomainName) / sizeof(szDomainName[0]);

    //3.LookupAccountSid関数で、トークンのSIDに対するアカウント情報を取得する
    LookupAccountSidA(NULL,
        pTokenUser->User.Sid,
        szAccountName,
        &dwAccountNameSize,
        szDomainName,
        &dwDomainNameSize,
        &snu);

    char buf[300];
    snprintf(buf, 300, "TokenUser - AccountName: %s, DomainName: %s\n", szAccountName, szDomainName);
    MessageBoxA(NULL, buf, "debug", MB_OK);

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); //Obtain the only local banner
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); //AdjustTokenPrivieges
	if (GetLastError() != ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "AdjustTokenPrivileges enable failed!", "debug", MB_OK); //Failed AdjustTokenPrivileges
	}
	MessageBoxA(NULL, "AdjustTokenPrivileges", "debug", MB_OK);
}

