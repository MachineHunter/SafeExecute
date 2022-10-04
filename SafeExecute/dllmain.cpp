#include "pch.h"
#include "hook.h"
#include "readchecklist.h"
#include "readmode.h"

char processPath[MAX_PATH];
char processDir[MAX_PATH];

DWORD WINAPI ThreadMain(LPVOID params) {
    GetModuleFileNameA(NULL, processPath, MAX_PATH);
    strcpy_s(processDir, processPath);
    PathRemoveFileSpecA(processDir);
    strcat_s(processDir, "\\");

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

