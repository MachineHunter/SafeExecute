#include "pch.h"
#include "hook.h"


// ================================== フックを追加する場合は、ここから =====================================================

// 1: WindowsAPIの関数型の定義
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* ISDEBUGGERPRESENT)();
SETFILEATTRIBUTESA orig_SetFileAttributesA;
ISDEBUGGERPRESENT orig_IsDebuggerPresent;


// 2: フック関数の用意（ココに悪性処理検出のロジックを書く）
bool WINAPI SetFileAttributesA_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) { 
    char oneself_file_path[MAX_PATH] = {};

    // 自分自身を隠しファイル化する挙動の検知
    if (0 != GetModuleFileNameA(NULL, oneself_file_path, MAX_PATH)) {
        if ((strcmp(lpFileName, oneself_file_path) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
            ExitProcess(1);
        }
    }
    return orig_SetFileAttributesA(lpFileName, dwFileAttributes);   
}

bool WINAPI IsDebuggerPresent_Hook() {
    // IsDebuggerPresent_Hook デバッガの存在を確認している挙動の検知
    MessageBoxA(NULL, "Hooked IsDebuggerPresent", "debug", MB_OK);
    ExitProcess(1);
    return orig_IsDebuggerPresent();
}


// 3: フックする全てのWindowsAPIのリスト
HookList hooklist = {
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_Hook),
        HookFunc("kernel32.dll", "IsDebuggerPresent", (void**)&orig_IsDebuggerPresent, (void*)IsDebuggerPresent_Hook)
};

// ================================== ここまでを編集してください！ =====================================================


void Hook() {
    for (HookFunc hookfunc : hooklist) {
        ULONG cbSize = 0;
        HANDLE hModule = GetModuleHandleA(0);

        *hookfunc.origfunc = (void*)GetProcAddress(GetModuleHandleA(hookfunc.dllname), hookfunc.funcname);
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