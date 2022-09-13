#include "pch.h"
#include "hook.h"


// ================================== �t�b�N��ǉ�����ꍇ�́A�������� =====================================================

// 1: WindowsAPI�̊֐��^�̒�`
typedef int(WINAPI* MESSAGEBOXA)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
typedef void(WINAPI* SLEEP)(DWORD dwMilliseconds);
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* ISDEBUGGERPRESENT)();
MESSAGEBOXA orig_MessageBoxA;
SLEEP orig_Sleep;
SETFILEATTRIBUTESA orig_SetFileAttributesA;
ISDEBUGGERPRESENT orig_IsDebuggerPresent; //���m�����猳�̃v���Z�X�ɖ߂邩�炱�ꂢ��Ȃ��H


// 2: �t�b�N�֐��̗p�Ӂi�R�R�Ɉ����������o�̃��W�b�N�������j
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

// FileAttributesA_FileAttributeHidden_Hook �������g���B���t�@�C�������鋓���̌��m
bool WINAPI SetFileAttributesA_FileAttributeHidden_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) { 
    char oneself_file_path[MAX_PATH] = {}; // ���s�t�@�C���i�������g�j�̃t���p�X���i�[

    if (0 != GetModuleFileNameA(NULL, oneself_file_path, MAX_PATH)) { // �������g�̃t�@�C���p�X�̎擾
        // ������: �������g�̃t�@�C���p�X, ������: FILE_ATTRIBUTE_HIDDEN �̏ꍇ ExitProcess
        if ((strcmp(lpFileName, oneself_file_path) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
            ExitProcess(1);
        }
    }
    return orig_SetFileAttributesA(lpFileName, dwFileAttributes);   
}

// IsDebuggerPresent_Hook �f�o�b�K�̑��݂��m�F���Ă��鋓���̌��m
bool WINAPI IsDebuggerPresent_Hook() {

    MessageBoxA(NULL, "Hooked IsDebuggerPresent", "debug", MB_OK);
    ExitProcess(1);
    return false; //�����̕Ԃ�l�K���ɐݒ肵����ł����ǂ܂����ł����ˁH
}

// 3: �t�b�N����S�Ă�WindowsAPI�̃��X�g
HookList hooklist = {
        HookFunc("user32.dll", "MessageBoxA", (void**)&orig_MessageBoxA, (void*)MessageBoxA_Hook),
        HookFunc("kernel32.dll", "Sleep", (void**)&orig_Sleep, (void*)Sleep_Hook),
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_FileAttributeHidden_Hook),
        HookFunc("kernel32.dll", "IsDebuggerPresent", (void**)&orig_IsDebuggerPresent, (void*)IsDebuggerPresent_Hook)
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