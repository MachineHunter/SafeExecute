#include "pch.h"
#include "hook.h"


// ================================== フックを追加する場合は、ここから =====================================================

// 1: WindowsAPIの関数型の定義
typedef int(WINAPI* MESSAGEBOXA)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
typedef void(WINAPI* SLEEP)(DWORD dwMilliseconds);
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
MESSAGEBOXA orig_MessageBoxA;
SLEEP orig_Sleep;
SETFILEATTRIBUTESA orig_SetFileAttributesA;


// 2: フック関数の容易（ココに悪性処理検出のロジックを書く）
int WINAPI MessageBoxA_Hook (
    HWND    hWnd,
    LPCTSTR lpText,
    LPCTSTR lpCaption,
    UINT    uType
) {
    MessageBoxA(NULL, "Hooked MessageBoxA", "debug", MB_OK);
    return orig_MessageBoxA(hWnd, lpText, lpCaption, uType);
}

void WINAPI Sleep_Hook(
    DWORD dwMilliseconds
) {
    MessageBoxA(NULL, "Hooked Sleep", "debug", MB_OK);
    return orig_Sleep(dwMilliseconds);
}

// FileAttributesA_FileAttributeHidden_Hook 自分自身を隠しファイル化する挙動の検知
bool WINAPI SetFileAttributesA_FileAttributeHidden_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) { 
    char init_char[MAX_PATH] = {}; // LPSTR の初期化用
    LPSTR oneself_file_path = init_char; // 実行ファイル（自分自身）のフルパスを格納

    if (0 != GetModuleFileNameA(NULL, oneself_file_path, MAX_PATH)) { // 自分自身のファイルパスの取得
        // 第一引数: 自分自身のファイルパス, 第二引数: FILE_ATTRIBUTE_HIDDEN の場合 ExitProcess
        if ((strcmp(lpFileName, oneself_file_path) == 0) && (dwFileAttributes == FILE_ATTRIBUTE_HIDDEN)) {
            ExitProcess(1);
        }
    }
    return orig_SetFileAttributesA(lpFileName, dwFileAttributes);   
}


// 3: フックする全てのWindowsAPIのリスト
HookList hooklist = {
        HookFunc("user32.dll", "MessageBoxA", (void**)&orig_MessageBoxA, (void*)MessageBoxA_Hook),
        HookFunc("kernel32.dll", "Sleep", (void**)&orig_Sleep, (void*)Sleep_Hook),
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_FileAttributeHidden_Hook)
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