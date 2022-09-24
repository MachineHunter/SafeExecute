#include "pch.h"
#include "hook.h"
#include <wininet.h>

int res;

// ================================== フックを追加する場合は、ここから =====================================================

// 1: WindowsAPIの関数型の定義
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* SETFILEATTRIBUTESW)(LPCWSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* ISDEBUGGERPRESENT)();
typedef BOOL(WINAPI* CREATEPROCESSA)(PCTSTR pszApplicationName, PTSTR  pszCommandLine, PSECURITY_ATTRIBUTES psaProcess, PSECURITY_ATTRIBUTES psaThread, BOOL   bInheritHandles, DWORD  fdwCreate, PVOID  pvEnvironment, PCTSTR pszCurDir, LPSTARTUPINFO  psiStartInfo, PPROCESS_INFORMATION ppiProcInfo);
typedef int(WINAPI* WSASTARTUP)(WORD wVersionRequired, LPWSADATA lpWSAData);
typedef HINTERNET (WINAPI* INTERNETOPENURLA)(HINTERNET hInternet, LPCSTR lpszUrl, LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
typedef LSTATUS(WINAPI* REGCREATEKEYEXA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
typedef LSTATUS(WINAPI* REGCREATEKEYEXW)(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
typedef BOOL(WINAPI* WRITEFILE)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
typedef BOOL(WINAPI* DELETEFILEW)(LPCWSTR lpFileName);
typedef BOOL(WINAPI* DELETEFILEA)(LPCSTR lpFileName);
typedef BOOL(WINAPI* MOVEFILEW)(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName);
typedef BOOL(WINAPI* CRYPTDECRYPT)(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE* pbData, DWORD* pdwDataLen);
SETFILEATTRIBUTESA orig_SetFileAttributesA;
SETFILEATTRIBUTESW orig_SetFileAttributesW;
ISDEBUGGERPRESENT orig_IsDebuggerPresent;
CREATEPROCESSA orig_CreateProcessA;
WSASTARTUP orig_WSAStartup;
INTERNETOPENURLA orig_InternetOpenUrlA;
REGCREATEKEYEXA orig_RegCreateKeyExA;
REGCREATEKEYEXW orig_RegCreateKeyExW;
WRITEFILE orig_WriteFile;
DELETEFILEW orig_DeleteFileW;
DELETEFILEA orig_DeleteFileA;
MOVEFILEW orig_MoveFileW;
CRYPTDECRYPT orig_CryptDecrypt;


// 2: フック関数の用意（ココに悪性処理検出のロジックを書く）
// （※ 関数冒頭で PreHook() を必ず呼んで欲しいです...!）
bool WINAPI SetFileAttributesA_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) {

    // 自分自身を隠しファイル化する挙動の検知
    if ((strcmp(lpFileName, processPath) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
        PreHook(3, "SetFileAttributesA", lpFileName, "FILE_ATTRIBUTE_HIDDEN");
        res = MsgBox("This executable is trying to make itself a hidden file\nContinue execution?");
        if (res == IDNO)
            ExitProcess(1);
    }
    return orig_SetFileAttributesA(lpFileName, dwFileAttributes);
}

bool WINAPI SetFileAttributesW_Hook(
    LPCWSTR lpFileName,
    DWORD dwFileAttributes
) {
    wchar_t text_wchar[MAX_PATH] = {};
    size_t pReturnValue = 0;
    mbstowcs_s(&pReturnValue, text_wchar, MAX_PATH, processPath, MAX_PATH);

    // 自分自身を隠しファイル化する挙動の検知
    if ((wcscmp(lpFileName, text_wchar) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
        PreHook(3, "SetFileAttributesW", WStringToString(lpFileName).c_str(), "FILE_ATTRIBUTE_HIDDEN");
        res = MsgBox("This executable is trying to make itself a hidden file\nContinue execution?");
        if (res == IDNO)
            ExitProcess(1);
    }
    return orig_SetFileAttributesW(lpFileName, dwFileAttributes);
}

bool WINAPI IsDebuggerPresent_Hook() {
    PreHook(1, "IsDebuggerPresent");
    // TODO: interactive
    ExitProcess(1);
    return orig_IsDebuggerPresent();
}

bool WINAPI CreateProcessA_Hook(
    PCTSTR pszApplicationName,
    PTSTR  pszCommandLine,
    PSECURITY_ATTRIBUTES psaProcess,
    PSECURITY_ATTRIBUTES psaThread,
    BOOL   bInheritHandles,
    DWORD  fdwCreate,
    PVOID  pvEnvironment,
    PCTSTR pszCurDir,
    LPSTARTUPINFO  psiStartInfo,
    PPROCESS_INFORMATION ppiProcInfo
) {
    PreHook(1, "CreateProcessA");
    // TODO: interactive
    ExitProcess(1);
    return orig_CreateProcessA(pszApplicationName, pszCommandLine, psaProcess, psaThread, bInheritHandles, fdwCreate, pvEnvironment, pszCurDir, psiStartInfo, ppiProcInfo);
}

int WINAPI WSAStartup_Hook(
    WORD wVersionRequired,
    LPWSADATA lpWSAData
) {
    PreHook(1, "WSAStartup");
    // TODO: interactive
    ExitProcess(1);
    return orig_WSAStartup(wVersionRequired, lpWSAData);
}

HINTERNET InternetOpenUrlA_Hook(
	HINTERNET hInternet,
	LPCSTR    lpszUrl,
	LPCSTR    lpszHeaders,
	DWORD     dwHeadersLength,
	DWORD     dwFlags,
	DWORD_PTR dwContext
) {
    PreHook(1, "InternetOpenUrlA");
    char buf[500];
    snprintf(buf, 500, "This executable attempt to access the URL below\n%s\nContinue execution?", lpszUrl);
    res = MsgBox(buf);
    if(res==IDNO)
        ExitProcess(1);
    return orig_InternetOpenUrlA(hInternet, lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext);
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
    // スタートアップレジストリへの登録の検知
    if ((_stricmp(lpSubKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == 0) && ((samDesired & KEY_SET_VALUE) != 0)){
        PreHook(3, "RegCreateKeyExA", lpSubKey, "KEY_SET_VALUE");
        res = MsgBox("Registration to startup registry detected\nBy doing this, the executable will automatically runs on system startup.\nContinue execution?");
        if (res == IDNO)
            ExitProcess(1);
    }

    return orig_RegCreateKeyExA(hkey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

LSTATUS WINAPI RegCreateKeyExW_Hook(
    HKEY hkey,
    LPCWSTR lpSubKey,
    DWORD Reserved,
    LPWSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
) { 
    // スタートアップレジストリへの登録の検知
    if ((_wcsicmp(lpSubKey, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == 0) && ((samDesired & KEY_SET_VALUE) != 0)) {
        setlocale(LC_ALL, "Japanese");
        PreHook(3, "RegCreateKeyExW", WStringToString(lpSubKey).c_str(), "KEY_SET_VALUE");
        res = MsgBox("Registration to startup registry detected\nBy doing this, the executable will automatically runs on system startup.\nContinue execution?");
        if(res == IDNO)
            ExitProcess(1);
    }
    return orig_RegCreateKeyExW(hkey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

bool WINAPI WriteFile_Hook(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
) {
    PreHook(1, "WriteFile");
    // TODO: interactive
    ExitProcess(1);
    return orig_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

bool WINAPI DeleteFileW_Hook(
    LPCWSTR lpFileName
) {
    PreHook(1, "DeleteFileW");
    // DeleteFileWの実行を検知
    ExitProcess(1);
    return orig_DeleteFileW(lpFileName);
}

bool WINAPI DeleteFileA_Hook(
    LPCSTR lpFileName
) {
    PreHook(1, "DeleteFileA");
    // DeleteFileAの実行を検知
    ExitProcess(1);
    return orig_DeleteFileA(lpFileName);
}

BOOL WINAPI MoveFileW_Hook(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName
) {
    PreHook(1, "MoveFileW");
    // MoveFile Hook
    ExitProcess(1);
    return orig_MoveFileW(lpExistingFileName, lpNewFileName);
}

BOOL WINAPI CryptDecrypt_Hook(
    HCRYPTKEY hKey,
    HCRYPTHASH hHash,
    BOOL Final,
    DWORD dwFlags,
    BYTE* pbData,
    DWORD* pdwDataLen
) {
    PreHook(1, "CryptDecrypt");
    res = MsgBox("Crypto Operation Detected\nContinue execution?");
    if (res == IDNO)
        ExitProcess(1);
    return orig_CryptDecrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen);
}


// 3: フックする全てのWindowsAPIのリスト
HookList hooklist = {
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_Hook),
        HookFunc("kernel32.dll", "SetFileAttributesW", (void**)&orig_SetFileAttributesW, (void*)SetFileAttributesW_Hook),
        HookFunc("kernel32.dll", "IsDebuggerPresent", (void**)&orig_IsDebuggerPresent, (void*)IsDebuggerPresent_Hook),
        HookFunc("kernel32.dll", "CreateProcessA", (void**)&orig_CreateProcessA, (void*)CreateProcessA_Hook),
        HookFunc("ws2_32.dll", WSAStartup_Ordinal, (void**)&orig_WSAStartup, (void*)WSAStartup_Hook),
        HookFunc("WinInet.dll", "InternetOpenUrlA", (void**)&orig_InternetOpenUrlA, (void*)InternetOpenUrlA_Hook),
        HookFunc("advapi32.dll", "RegCreateKeyExA", (void**)&orig_RegCreateKeyExA, (void*)RegCreateKeyExA_Hook),
        HookFunc("advapi32.dll", "RegCreateKeyExW", (void**)&orig_RegCreateKeyExW, (void*)RegCreateKeyExW_Hook),
        HookFunc("kernel32.dll", "WriteFile", (void**)&orig_WriteFile, (void*)WriteFile_Hook),
        HookFunc("kernel32.dll", "DeleteFileW", (void**)&orig_DeleteFileW, (void*)DeleteFileW_Hook),
        HookFunc("kernel32.dll", "DeleteFileA", (void**)&orig_DeleteFileA, (void*)DeleteFileA_Hook),
        HookFunc("kernel32.dll", "MoveFileW", (void**)&orig_MoveFileW, (void*)MoveFileW_Hook),
        HookFunc("advapi32.dll", "CryptDecrypt", (void**)&orig_CryptDecrypt, (void*)CryptDecrypt_Hook)
};

// ================================== ここまでを編集してください！ =====================================================

void Hook() {
    for (HookFunc hookfunc : hooklist) {
        if (!hookfunc.isChecked) continue;

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


std::string WStringToString(const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}
