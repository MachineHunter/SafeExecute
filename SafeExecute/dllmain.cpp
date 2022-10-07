#include "pch.h"
#include "hook.h"
#include "readchecklist.h"
#include "readmode.h"

char processPath[MAX_PATH];
char localDir[MAX_PATH];

DWORD WINAPI ThreadMain(LPVOID params) {
    GetModuleFileNameA(NULL, processPath, MAX_PATH);
    ExpandEnvironmentStringsA("%LOCALAPPDATA%", localDir, MAX_PATH);
    strcat_s(localDir, "\\安全実行侍～俺を信じろ～");

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

