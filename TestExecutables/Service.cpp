#include <Windows.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// check if admin
	BOOL isAdmin;
	isAdmin = SHTestTokenMembership(NULL, DOMAIN_ALIAS_RID_ADMINS);
	if(!isAdmin) {
		MessageBoxA(NULL, "you have to be admin to execute this", "Error", MB_OK);
		return 0;
	}

	// check if executed by user or service
	HANDLE       hToken;
	PTOKEN_USER  tokenInfo;
	DWORD        retLen;
	char         accountName[100];
	DWORD        accountNameSize = 100;
	char         domainName[100];
	DWORD        domainNameSize = 100;
	SID_NAME_USE snu;

	OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
	tokenInfo = (PTOKEN_USER)LocalAlloc(LPTR, 100);
	GetTokenInformation(hToken, TokenUser, tokenInfo, 100, &retLen);
	LookupAccountSidA(NULL, tokenInfo->User.Sid, accountName, &accountNameSize, domainName, &domainNameSize, &snu);

	if(strstr(domainName, "NT AUTHORITY")) {
		// when executed by service
		// do nothing :)
	}
	else{
		// when executed by user
		char processPath[MAX_PATH];
		GetModuleFileName(NULL, processPath, MAX_PATH);

		SC_HANDLE hSCManager;
		SC_HANDLE hService;
		char serviceName[] = "HogeHogeService";
		hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if(hSCManager != NULL) {
			hService = CreateServiceA(
				hSCManager,
				serviceName,
				serviceName,
				SERVICE_ALL_ACCESS,
				SERVICE_WIN32_OWN_PROCESS,
				SERVICE_DEMAND_START,
				SERVICE_ERROR_IGNORE,
				processPath,
				NULL, NULL, NULL, NULL, NULL);
			StartServiceA(hService, NULL, NULL);
			CloseServiceHandle(hService);
		}
		CloseServiceHandle(hSCManager);

		MessageBoxA(NULL, "Created HogeHogeService that does nothing!", serviceName, MB_OK);
	}

	return 0;
}
