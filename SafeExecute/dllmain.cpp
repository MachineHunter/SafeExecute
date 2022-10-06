#include "pch.h"
#include "hook.h"
#include "readchecklist.h"
#include "readmode.h"

char processPath[MAX_PATH];
char localDir[MAX_PATH];

DWORD WINAPI ThreadMain(LPVOID params) {
    MessageBoxA(NULL, "ThreadMain", "debug", MB_OK);
    GetModuleFileNameA(NULL, processPath, MAX_PATH);
    MessageBoxA(NULL, "getmodulefilename after", "debug", MB_OK);
    ExpandEnvironmentStringsA("%LOCALAPPDATA%", localDir, MAX_PATH);
    MessageBoxA(NULL, localDir, "debug", MB_OK);
    strcat_s(localDir, "\\安全実行侍～俺を信じろ～\\");

    ReadMode();
    ReadCheckList();
    Hook();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, ThreadMain, hModule, 0, 0);
    }
    return TRUE;
}

