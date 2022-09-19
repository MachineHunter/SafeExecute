#include "pch.h"
#include "hook.h"


// ================================== フックを追加する場合は、ここから =====================================================

// 1: WindowsAPIの関数型の定義
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* ISDEBUGGERPRESENT)();
typedef int(WINAPI* WSASTARTUP)(WORD wVersionRequired, LPWSADATA lpWSAData);
SETFILEATTRIBUTESA orig_SetFileAttributesA;
ISDEBUGGERPRESENT orig_IsDebuggerPresent;
WSASTARTUP orig_WSAStartup;


// 2: フック関数の用意（ココに悪性処理検出のロジックを書く）
// （※ 関数冒頭で PreHook() を必ず呼んで欲しいです...!）
bool WINAPI SetFileAttributesA_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) { 
    PreHook("SetFileAttributesA");

    // 自分自身を隠しファイル化する挙動の検知
    if ((strcmp(lpFileName, processPath) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
        ExitProcess(1);
    }
    return orig_SetFileAttributesA(lpFileName, dwFileAttributes);   
}

bool WINAPI IsDebuggerPresent_Hook() {
    PreHook("IsDebuggerPresent");

    // IsDebuggerPresent_Hook デバッガの存在を確認している挙動の検知
    MessageBoxA(NULL, "Hooked IsDebuggerPresent", "debug", MB_OK);
    ExitProcess(1);
    return orig_IsDebuggerPresent();
}

int WINAPI WSAStartup_Hook(
    WORD wVersionRequired,
    LPWSADATA lpWSAData
) {
    PreHook("WSAStartup");
    MessageBoxA(NULL, "Hooked WSAStartup", "debug", MB_OK);
    ExitProcess(1);
    return orig_WSAStartup(wVersionRequired, lpWSAData);
}


// 3: フックする全てのWindowsAPIのリスト
HookList hooklist = {
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_Hook),
        HookFunc("kernel32.dll", "IsDebuggerPresent", (void**)&orig_IsDebuggerPresent, (void*)IsDebuggerPresent_Hook),
        HookFunc("ws2_32.dll", WSAStartup_Ordinal, (void**)&orig_WSAStartup, (void*)WSAStartup_Hook)
};

// ================================== ここまでを編集してください！ =====================================================

void Hook() {
    for (HookFunc hookfunc : hooklist) {
        ULONG cbSize = 0;
        HANDLE hModule = GetModuleHandleA(0);

        if (hookfunc.isOrdinal)
            *hookfunc.origfunc = (void*)GetProcAddress(GetModuleHandleA(hookfunc.dllname), MAKEINTRESOURCEA(hookfunc.func.ordinal));
        else
            *hookfunc.origfunc = (void*)GetProcAddress(GetModuleHandleA(hookfunc.dllname), hookfunc.func.name);

        PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &cbSize);

        for (; pImageImportDescriptor->Name; pImageImportDescriptor++) {
            LPCSTR pModuleName = (LPCSTR)((PBYTE)hModule + pImageImportDescriptor->Name);
            DWORD ModuleBase = (DWORD)GetModuleHandleA(pModuleName);

            PIMAGE_THUNK_DATA pFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->FirstThunk);
            PIMAGE_THUNK_DATA pOriginalFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->OriginalFirstThunk);

            for (; pFirstThunk->u1.Function; pFirstThunk++, pOriginalFirstThunk++) {
                FARPROC pfnImportedFunc = (FARPROC)(pFirstThunk->u1.Function);
                PIMAGE_IMPORT_BY_NAME pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hModule + pOriginalFirstThunk->u1.AddressOfData);

                if (pfnImportedFunc == (FARPROC)*hookfunc.origfunc) {
                    MEMORY_BASIC_INFORMATION mbi;
                    DWORD dwJunk = 0;
                    
                    VirtualQuery(pFirstThunk, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
                    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
                    pFirstThunk->u1.Function = (ULONGLONG)(DWORD_PTR)hookfunc.hook;
                    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &dwJunk);
                    break;
                }
            }
        }
    }
}