#include "pch.h"
#include "hook.h"


// ================================== �t�b�N��ǉ�����ꍇ�́A�������� =====================================================

// 1: WindowsAPI�̊֐��^�̒�`
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* ISDEBUGGERPRESENT)();
typedef LSTATUS(WINAPI* REGCREATEKEYEXA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);

SETFILEATTRIBUTESA orig_SetFileAttributesA;
ISDEBUGGERPRESENT orig_IsDebuggerPresent;
REGCREATEKEYEXA orig_RegCreateKeyExA;


// 2: �t�b�N�֐��̗p�Ӂi�R�R�Ɉ����������o�̃��W�b�N�������j
// �i�� �֐��`���� PreHook() ��K���Ă�ŗ~�����ł�...!�j
bool WINAPI SetFileAttributesA_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) {
    PreHook("SetFileAttributesA");

    // �������g���B���t�@�C�������鋓���̌��m
    if ((strcmp(lpFileName, processPath) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
        ExitProcess(1);
    }
    return orig_SetFileAttributesA(lpFileName, dwFileAttributes);
}

bool WINAPI IsDebuggerPresent_Hook() {
    PreHook("IsDebuggerPresent");

    // IsDebuggerPresent_Hook �f�o�b�K�̑��݂��m�F���Ă��鋓���̌��m
    MessageBoxA(NULL, "Hooked IsDebuggerPresent", "debug", MB_OK);
    ExitProcess(1);
    return orig_IsDebuggerPresent();
}

LSTATUS WINAPI RegCreateKeyExA_Hook(
    HKEY hkey,
    LPCSTR lpSubKey,
    DWORD Reserved,
    LPSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
) {
    PreHook("RegCreateKeyExA");
    // �X�^�[�g�A�b�v���W�X�g���ւ̓o�^�̌��m
    if ((_stricmp(lpSubKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == 0) && ((samDesired & KEY_SET_VALUE) != 0)){
        ExitProcess(1);
    }

    return orig_RegCreateKeyExA(hkey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}


// 3: �t�b�N����S�Ă�WindowsAPI�̃��X�g
HookList hooklist = {
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_Hook),
        HookFunc("kernel32.dll", "IsDebuggerPresent", (void**)&orig_IsDebuggerPresent, (void*)IsDebuggerPresent_Hook),
        HookFunc("advapi32.dll", "RegCreateKeyExA", (void**)&orig_RegCreateKeyExA, (void*)RegCreateKeyExA_Hook)
};

// ================================== �����܂ł�ҏW���Ă��������I =====================================================


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