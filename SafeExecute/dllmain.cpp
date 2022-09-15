#include "pch.h"
#include "hook.h"

char processPath[MAX_PATH];

DWORD WINAPI ThreadMain(LPVOID params) {
    GetModuleFileNameA(NULL, processPath, MAX_PATH);
    Hook();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, ThreadMain, hModule, 0, 0);
    }
    return TRUE;
}

