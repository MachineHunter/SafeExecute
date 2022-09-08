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

	SC_HANDLE hSCManager;
	SC_HANDLE hService;
	char serviceName[] = "HogeHogeService";
	hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(hSCManager != NULL) {
		hService = OpenServiceA (
			hSCManager,
			serviceName,
			SERVICE_ALL_ACCESS);
		DeleteService(hService);
		CloseServiceHandle(hService);
	}
	CloseServiceHandle(hSCManager);
	return 0;
}
