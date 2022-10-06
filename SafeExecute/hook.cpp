#include "pch.h"
#include "hook.h"

int res;
bool CreateProcessChecked = false;

std::string WStringToString(const std::wstring& ws) {
    std::string s(ws.length(), ' ');
    std::copy(ws.begin(), ws.end(), s.begin());
    return s;
}

std::string PathToFileName(char* path) {
    string strFilePath(path);
    string strFileName;
    size_t off = strFilePath.find_last_of("/\\");
    if (off != string::npos)
        strFileName = strFilePath.substr(off + 1);
    else
        strFileName = strFilePath;

    return strFileName;
}

bool IsSafeExecuteFilesA(LPSTR lpFileName) {
    char fullPath[MAX_PATH];
    GetFullPathNameA(lpFileName, MAX_PATH, fullPath, NULL);

    string strFullPath(fullPath);
    string safeExecutePath(localDir);
    transform(strFullPath.begin(), strFullPath.end(), strFullPath.begin(), ::toupper);
    transform(safeExecutePath.begin(), safeExecutePath.end(), safeExecutePath.begin(), ::toupper);

    if (strFullPath.find(safeExecutePath) != std::string::npos)
        return true;
    return false;
}

bool IsSafeExecuteFilesW(LPWSTR lpFileName) {
    char fullPath[MAX_PATH];
    GetFullPathNameA(WStringToString(lpFileName).c_str(), MAX_PATH, fullPath, NULL);

    string strFullPath(fullPath);
    string safeExecutePath(localDir);
    transform(strFullPath.begin(), strFullPath.end(), strFullPath.begin(), ::toupper);
    transform(safeExecutePath.begin(), safeExecutePath.end(), safeExecutePath.begin(), ::toupper);

    if (strFullPath.find(safeExecutePath) != std::string::npos)
        return true;
    return false;
}




// ================================== フックを追加する場合は、ここから =====================================================

// 1: WindowsAPIの関数型の定義
typedef BOOL(WINAPI* SETFILEATTRIBUTESA)(LPCSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* SETFILEATTRIBUTESW)(LPCWSTR lpFileName, DWORD dwFileAttributes);
typedef BOOL(WINAPI* ISDEBUGGERPRESENT)();
typedef BOOL(WINAPI* CREATEPROCESSA)(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD  dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA  lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
typedef BOOL(WINAPI* CREATEPROCESSW)(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID  lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
typedef INT(WSAAPI* INETPTON)(INT Family, PCSTR pszAddrString, PVOID pAddrBuf);
typedef HINTERNET (WINAPI* INTERNETOPENURLA)(HINTERNET hInternet, LPCSTR lpszUrl, LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
typedef HINTERNET(WINAPI* INTERNETOPENURLW)(HINTERNET hInternet, LPCWSTR lpszUrl, LPCWSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
typedef LSTATUS(WINAPI* REGCREATEKEYEXA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
typedef LSTATUS(WINAPI* REGCREATEKEYEXW)(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
typedef HANDLE(WINAPI* CREATEFILEA)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef HANDLE(WINAPI* CREATEFILEW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef BOOL(WINAPI* WRITEFILE)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
typedef BOOL(WINAPI* DELETEFILEW)(LPCWSTR lpFileName);
typedef BOOL(WINAPI* DELETEFILEA)(LPCSTR lpFileName);
typedef BOOL(WINAPI* MOVEFILEA)(LPCSTR lpExistingFileName, LPCSTR lpNewFileName);
typedef BOOL(WINAPI* MOVEFILEW)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName);
typedef BOOL(WINAPI* MOVEFILEEXA)(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, DWORD  dwFlags);
typedef BOOL(WINAPI* MOVEFILEEXW)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD  dwFlags);
typedef HANDLE(WINAPI* FINDFIRSTFILEA)(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
typedef BOOL(WINAPI* FINDNEXTFILEA)(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
typedef HANDLE(WINAPI* FINDFIRSTFILEW)(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
typedef BOOL(WINAPI* FINDNEXTFILEW)(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
typedef BOOL(WINAPI* CRYPTDECRYPT)(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE* pbData, DWORD* pdwDataLen);
typedef SC_HANDLE(WINAPI* CREATESERVICEA)(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword);
typedef SC_HANDLE(WINAPI* CREATESERVICEW)(SC_HANDLE hSCManager, LPCWSTR lpServiceName, LPCWSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCWSTR lpBinaryPathName, LPCWSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCWSTR lpDependencies, LPCWSTR lpServiceStartName, LPCWSTR lpPassword);
typedef BOOL(WINAPI* OPENPROCESSTOKEN)(HANDLE  ProcessHandle, DWORD   DesiredAccess, PHANDLE TokenHandle);
typedef BOOL(WINAPI* ADJUSTTOKENPRIVILEGES)(HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, PDWORD ReturnLength);
typedef INT(WINAPI* GETLOCALEINFOA)(LCID Locale, LCTYPE LCType, LPSTR lpLCData, int cchData);
typedef INT(WINAPI* GETLOCALEINFOW)(LCID Locale, LCTYPE LCType, LPWSTR lpLCData, int cchData);
typedef INT(WINAPI* GETLOCALEINFOEX)(LPCWSTR lpLocaleName, LCTYPE LCType, LPWSTR lpLCData, int cchData);
typedef BOOL(WINAPI* CREATETIMERQUEUETIMER)(PHANDLE phNewTimer, HANDLE TimerQueue, WAITORTIMERCALLBACK Callback, PVOID Parameter, DWORD DueTime, DWORD Period, ULONG Flags);
typedef BOOL(WINAPI* SYSTEMPARAMETERSINFOA)(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
typedef BOOL(WINAPI* SYSTEMPARAMETERSINFOW)(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
typedef HRESULT(WINAPI* URLDOWNLOADTOFILEA)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, _Reserved_ DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB);
typedef HRESULT(WINAPI* URLDOWNLOADTOFILEW)(LPUNKNOWN pCaller, LPCWSTR szURL, LPCWSTR szFileName, _Reserved_ DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB);
SETFILEATTRIBUTESA orig_SetFileAttributesA;
SETFILEATTRIBUTESW orig_SetFileAttributesW;
ISDEBUGGERPRESENT orig_IsDebuggerPresent;
CREATEPROCESSA orig_CreateProcessA;
CREATEPROCESSW orig_CreateProcessW;
INETPTON orig_inet_pton;
INTERNETOPENURLA orig_InternetOpenUrlA;
INTERNETOPENURLW orig_InternetOpenUrlW;
REGCREATEKEYEXA orig_RegCreateKeyExA;
REGCREATEKEYEXW orig_RegCreateKeyExW;
CREATEFILEA orig_CreateFileA;
CREATEFILEW orig_CreateFileW;
WRITEFILE orig_WriteFile;
DELETEFILEW orig_DeleteFileW;
DELETEFILEA orig_DeleteFileA;
MOVEFILEA orig_MoveFileA;
MOVEFILEW orig_MoveFileW;
MOVEFILEEXA orig_MoveFileExA;
MOVEFILEEXW orig_MoveFileExW;
FINDFIRSTFILEA orig_FindFirstFileA;
FINDNEXTFILEA orig_FindNextFileA;
CRYPTDECRYPT orig_CryptDecrypt;
FINDFIRSTFILEW orig_FindFirstFileW;
FINDNEXTFILEW orig_FindNextFileW;
CREATESERVICEA orig_CreateServiceA;
CREATESERVICEW orig_CreateServiceW;
OPENPROCESSTOKEN orig_OpenProcessToken;
ADJUSTTOKENPRIVILEGES orig_AdjustTokenPrivileges;
GETLOCALEINFOA orig_GetLocaleInfoA;
GETLOCALEINFOW orig_GetLocaleInfoW;
GETLOCALEINFOEX orig_GetLocaleInfoEx;
CREATETIMERQUEUETIMER orig_CreateTimerQueueTimer;
SYSTEMPARAMETERSINFOA orig_SystemParametersInfoA;
SYSTEMPARAMETERSINFOW orig_SystemParametersInfoW;
URLDOWNLOADTOFILEA orig_URLDownloadToFileA;
URLDOWNLOADTOFILEW orig_URLDownloadToFileW;



// 2: フック関数の用意（ココに悪性処理検出のロジックを書く）
// （※ PreHook() を必ず呼んで欲しいです...!）
bool WINAPI SetFileAttributesA_Hook(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
) {

    // 自分自身を隠しファイル化する挙動の検知
    if ((strcmp(lpFileName, processPath) == 0) && ((dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)) {
        PreHook(3, "SetFileAttributesA", lpFileName, "FILE_ATTRIBUTE_HIDDEN");
        res = MsgBox("This executable is trying to make itself a hidden file.\nThis behavior is more common in malware than cleaware.\nContinue execution?");
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
        res = MsgBox("This executable is trying to make itself a hidden file.\nThis behavior is more common in malware than cleaware.\nContinue execution?");
        if (res == IDNO)
            ExitProcess(1);
    }
    return orig_SetFileAttributesW(lpFileName, dwFileAttributes);
}

bool WINAPI IsDebuggerPresent_Hook() {
    PreHook(1, "IsDebuggerPresent");
    res = MsgBox("This executable is trying to know whether you are using debugger.\nThis function is often used in malware to avoid being analyzed.\nContinue execution?");
    if (res == IDNO)
        ExitProcess(1);
    return orig_IsDebuggerPresent();
}

bool WINAPI CreateProcessA_Hook(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
) {
    if (CreateProcessChecked) {
        PreHook(1, "CreateProcessA");
        char buf[300];
        if (lpApplicationName == NULL)
            snprintf(buf, 300, "This executable is trying to execute a file below\n%s\nContinue execution?", lpCommandLine);
        else {
            if(lpCommandLine==NULL)
                snprintf(buf, 300, "This executable is trying to execute a file below\n%s\nContinue execution?", lpApplicationName);
            else
                snprintf(buf, 300, "This executable is trying to execute a file below\n%s %s\nContinue execution?", lpApplicationName, lpCommandLine);
        }
        res = MsgBox(buf);
        if (res == IDNO)
            ExitProcess(1);
    }
    
    BOOL suspended = ((dwCreationFlags & CREATE_SUSPENDED) != 0);
    dwCreationFlags |= CREATE_SUSPENDED;
    BOOL res2 = orig_CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);

    
    // inject SafeExecute.dll to child process
    FARPROC lib = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    char dllpath[MAX_PATH];
    GetModuleFileNameA(GetModuleHandleA("SafeExecute.dll"), dllpath, MAX_PATH);
    size_t dllpathSize = strlen(dllpath);
    LPVOID allocMem = VirtualAllocEx(lpProcessInformation->hProcess, NULL, dllpathSize, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(lpProcessInformation->hProcess, allocMem, dllpath, dllpathSize, NULL);
    CreateRemoteThread(lpProcessInformation->hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lib, allocMem, 0, NULL);
    Sleep(200);

    if (!suspended)
        ResumeThread(lpProcessInformation->hThread);
    return res2;
}

BOOL WINAPI CreateProcessW_Hook (
    LPCWSTR lpApplicationName,
    LPWSTR  lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID  lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
) {
    if (CreateProcessChecked) {
        PreHook(1, "CreateProcessW");
        char buf[300];
        if (lpApplicationName == NULL)
            snprintf(buf, 300, "This executable is trying to execute a file below\n%S\nContinue execution?", lpCommandLine);
        else {
            if (lpCommandLine == NULL)
                snprintf(buf, 300, "This executable is trying to execute a file below\n%S\nContinue execution?", lpApplicationName);
            else
                snprintf(buf, 300, "This executable is trying to execute a file below\n%S %S\nContinue execution?", lpApplicationName, lpCommandLine);
        }
        res = MsgBox(buf);
        if (res == IDNO)
            ExitProcess(1);
    }

    BOOL suspended = ((dwCreationFlags & CREATE_SUSPENDED) != 0);
    dwCreationFlags |= CREATE_SUSPENDED;
    BOOL res2 = orig_CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);

    // inject SafeExecute.dll to child process
    FARPROC lib = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    char dllpath[MAX_PATH];
    GetModuleFileNameA(GetModuleHandleA("SafeExecute.dll"), dllpath, MAX_PATH);
    size_t dllpathSize = strlen(dllpath);
    LPVOID allocMem = VirtualAllocEx(lpProcessInformation->hProcess, NULL, dllpathSize, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(lpProcessInformation->hProcess, allocMem, dllpath, dllpathSize, NULL);
    CreateRemoteThread(lpProcessInformation->hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lib, allocMem, 0, NULL);
    Sleep(200);

    if (!suspended)
        ResumeThread(lpProcessInformation->hThread);
    return res2;
}

int WSAAPI inet_pton_Hook(
    INT Family,
    PCSTR pszAddrString,
    PVOID pAddrBuf
) {
    PreHook(1, "inet_pton");
    char buf[300];
    snprintf(buf, 300, "This executable attempt to access IP address below\n%s\nContinue execution?", pszAddrString);
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_inet_pton(Family, pszAddrString, pAddrBuf);
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
    char buf[300];
    snprintf(buf, 300, "This executable attempt to access URL below\n%s\nContinue execution?", lpszUrl);
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_InternetOpenUrlA(hInternet, lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext);
}

HINTERNET InternetOpenUrlW_Hook(
    HINTERNET hInternet,
    LPCWSTR   lpszUrl,
    LPCWSTR   lpszHeaders,
    DWORD     dwHeadersLength,
    DWORD     dwFlags,
    DWORD_PTR dwContext
) {
    PreHook(1, "InternetOpenUrlW");
    char buf[300];
    snprintf(buf, 300, "This executable attempt to access URL below\n%ls\nContinue execution?", lpszUrl);
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_InternetOpenUrlW(hInternet, lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext);
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
    if ((_stricmp(lpSubKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == 0) && ((samDesired & KEY_SET_VALUE) != 0)) {
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
        if (res == IDNO)
            ExitProcess(1);
    }
    return orig_RegCreateKeyExW(hkey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

HANDLE WINAPI CreateFileA_Hook(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
) {
    if (IsSafeExecuteFilesA((LPSTR)lpFileName)) {
        res = MsgBox("This executable tried to open SafeExecute's files.\nSafeExecute's files contain backups files which should not be modified\nContinue execution? (No recommended)");
        if (res == IDNO)
            ExitProcess(1);
    }

    if (dwCreationDisposition == OPEN_ALWAYS || dwCreationDisposition == OPEN_EXISTING) {
        string strFileName;
        strFileName = PathToFileName((LPSTR)lpFileName);

        char path[MAX_PATH];
        strcpy_s(path, localDir);
        strcat_s(path, "backups\\");

        if (!PathFileExistsA(path))
            CreateDirectoryA(path, NULL);

        char buf[50];
        memset(buf, 0, 50);
        
        string strProcPath;
        strProcPath = PathToFileName(processPath);

        strcat_s(path, strProcPath.c_str());

        CreateDirectoryA(path, NULL);
        
        strcat_s(path, "\\");
        strcat_s(path, strFileName.c_str());
        CopyFileA(lpFileName, path, FALSE);
    }
    
    return orig_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI CreateFileW_Hook(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
) {
    if (IsSafeExecuteFilesW((LPWSTR)lpFileName)) {
        res = MsgBox("This executable tried to open SafeExecute's files.\nSafeExecute's files contain backups files which should not be modified\nContinue execution? (No recommended)");
        if (res == IDNO)
            ExitProcess(1);
    }

    if (dwCreationDisposition == OPEN_ALWAYS || dwCreationDisposition == OPEN_EXISTING) {
        string strFileName;
        strFileName = PathToFileName((LPSTR)WStringToString(lpFileName).c_str());

        char path[MAX_PATH];
        strcpy_s(path, localDir);
        strcat_s(path, "backups\\");

        if (!PathFileExistsA(path))
            CreateDirectoryA(path, NULL);

        char buf[50];
        memset(buf, 0, 50);

        string strProcPath;
        strProcPath = PathToFileName(processPath);

        strcat_s(path, strProcPath.c_str());

        CreateDirectoryA(path, NULL);

        strcat_s(path, "\\");
        strcat_s(path, strFileName.c_str());
        CopyFileA(WStringToString(lpFileName).c_str(), path, FALSE);
    }

    return orig_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

bool WINAPI WriteFile_Hook(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
) {
    PreHook(1, "WriteFile");

    char Path[300];
    GetFinalPathNameByHandleA(hFile, Path, 300, FILE_NAME_OPENED);
    char buf_msg[512];
    
    sprintf_s(buf_msg, 512, "This executable is trying to write to the following file\n \" %s \" \nContinue execution ? ", (const char*)Path);
    
    res = MsgBox(buf_msg);
    if (res == IDNO)
        ExitProcess(1);
    
    return orig_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

bool WINAPI DeleteFileW_Hook(
    LPCWSTR lpFileName
) {
    PreHook(1, "DeleteFileW");
    // DeleteFileWの実行を検知
    char buf_msg[500];
    sprintf_s(buf_msg, "This executable is trying to delete a file below\n%S\nContinue execution?", WStringToString(lpFileName).c_str());
    res = MsgBox(buf_msg);
    if (res == IDNO)
        ExitProcess(1);
    return orig_DeleteFileW(lpFileName);
}

bool WINAPI DeleteFileA_Hook(
    LPCSTR lpFileName
) {
    PreHook(1, "DeleteFileA");
    // DeleteFileAの実行を検知
    char buf_msg[500];
    sprintf_s(buf_msg, "This executable is trying to delete a file below\n%s\nContinue execution?", lpFileName);
    res = MsgBox(buf_msg);
    if (res == IDNO)
        ExitProcess(1);
    return orig_DeleteFileA(lpFileName);
}

BOOL WINAPI MoveFileA_Hook(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName
) {
    PreHook(1, "MoveFileA");
    // MoveFileA Hook
    char buf_msg[128];
    sprintf_s(buf_msg, "This executable is trying to rename %s to %s\nContinue execution ? ", (const char*) lpExistingFileName, (const char*) lpNewFileName);
    res = MsgBox(buf_msg);
    if (res == IDNO)
        ExitProcess(1);
    return orig_MoveFileA(lpExistingFileName, lpNewFileName);
}

BOOL WINAPI MoveFileW_Hook(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName
) {
    PreHook(1, "MoveFileW");
    // MoveFileW Hook
    char buf_msg[128];
    sprintf_s(buf_msg, "This executable is trying to rename %lS to %lS\nContinue execution ? ", lpExistingFileName, lpNewFileName);
    res = MsgBox(buf_msg);
    if (res == IDNO)
        ExitProcess(1);
    return orig_MoveFileW(lpExistingFileName, lpNewFileName);
}

bool WINAPI MoveFileExA_Hook(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName,
    DWORD  dwFlags
) {
    PreHook(1, "MoveFileExA");

    char buf_msg[128];
    sprintf_s(buf_msg, "This executable is trying to rename %s to %s\nContinue execution ? ", lpExistingFileName, lpNewFileName);
    res = MsgBox(buf_msg);

    if (res == IDNO)
        ExitProcess(1);

    return orig_MoveFileExA(lpExistingFileName, lpNewFileName, dwFlags);
}

bool WINAPI MoveFileExW_Hook(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName,
    DWORD  dwFlags
) {
    PreHook(1, "MoveFileExW");

    char buf_msg[128];
    sprintf_s(buf_msg, "This executable is trying to rename %S to %S\nContinue execution ? ", lpExistingFileName, lpNewFileName);
    res = MsgBox(buf_msg);

    if (res == IDNO)
        ExitProcess(1);

    return orig_MoveFileExW(lpExistingFileName, lpNewFileName, dwFlags);
}

HANDLE WINAPI FindFirstFileA_Hook(
    LPCSTR lpFileName,
    LPWIN32_FIND_DATAA lpFindFileData
) {
    PreHook(2, "FindFirstFileA", lpFileName);

    char buf_msg[500];
    sprintf_s(buf_msg, "File iteration started.\nThis executable is trying to iterate through file from '%s'.\nFile iteration can be used in normal executables but is also used in ransomeware to look for files to encrypt.\nContinue execution? ", lpFileName);
    res = MsgBox(buf_msg);

    if (res == IDNO)
        ExitProcess(1);

    return orig_FindFirstFileA(lpFileName, lpFindFileData);;
}

BOOL skipFileIterA = false;
BOOL WINAPI FindNextFileA_Hook(
    HANDLE hFindFile,
    LPWIN32_FIND_DATAA lpFindFileData
) {
    char prevFileName[MAX_PATH];
    strcpy_s(prevFileName, lpFindFileData->cFileName);
    BOOL ret = orig_FindNextFileA(hFindFile, lpFindFileData);
    
    if (!skipFileIterA && strcmp(lpFindFileData->cFileName, ".") && strcmp(lpFindFileData->cFileName, "..")) {
        PreHook(2, "FindNextFileA", lpFindFileData->cFileName);

        char buf_msg[500];
        sprintf_s(buf_msg, "File iteration currently at '%s'.\nFile iteration is also used in ransomeware to look for files to encrypt.\nPrevious iterated file is '%s'.\nIf this file is encrypted, then this executable maybe a ransomware.\nContinue execution?\n\nPress 'Cancel' to skip file iteration detection.", lpFindFileData->cFileName, prevFileName);
        res = MessageBoxA(NULL, buf_msg, "SafeExecute", MB_YESNOCANCEL);
        if (res == IDNO)
            ExitProcess(1);
        else if (res == IDCANCEL)
            skipFileIterA = true;
    }
    return ret;
}

HANDLE WINAPI FindFirstFileW_Hook(
    LPCWSTR lpFileName,
    LPWIN32_FIND_DATAW lpFindFileData
) {
    PreHook(2, "FindFirstFileW", WStringToString(lpFileName).c_str());

    char buf_msg[500];
    sprintf_s(buf_msg, "File iteration started.\nThis executable is trying to iterate through file from '%S'.\nFile iteration can be used in normal executables but is also used in ransomeware to look for files to encrypt.\nContinue execution? ", lpFileName);
    res = MsgBox(buf_msg);

    if (res == IDNO)
        ExitProcess(1);

    return orig_FindFirstFileW(lpFileName, lpFindFileData);;
}

BOOL skipFileIterW = false;
BOOL WINAPI FindNextFileW_Hook(
    HANDLE hFindFile,
    LPWIN32_FIND_DATAW lpFindFileData
) {
    char prevFileName[MAX_PATH];
    strcpy_s(prevFileName, WStringToString(lpFindFileData->cFileName).c_str());
    BOOL ret = orig_FindNextFileW(hFindFile, lpFindFileData);
    
    if (!skipFileIterW && wcscmp(lpFindFileData->cFileName, L".") && wcscmp(lpFindFileData->cFileName, L"..")) {
        PreHook(2, "FindNextFileW", WStringToString(lpFindFileData->cFileName).c_str());

        char buf_msg[500];
        sprintf_s(buf_msg, "File iteration currently at '%S'.\nFile iteration is also used in ransomeware to look for files to encrypt.\nPrevious iterated file is '%s'.\nIf this file is encrypted, then this executable maybe a ransomware.\nContinue execution?\n\nPress 'Cancel' to skip file iteration detection.", lpFindFileData->cFileName, prevFileName);
        res = MessageBoxA(NULL, buf_msg, "SafeExecute", MB_YESNOCANCEL);
        if (res == IDNO)
            ExitProcess(1);
        else if (res == IDCANCEL)
            skipFileIterW = true;
    }
    return ret;
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
    res = MsgBox("Crypto Operation Detected\nThese operations are often seen in malware.\nContinue execution?");
    if (res == IDNO)
        ExitProcess(1);
    return orig_CryptDecrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen);
}

SC_HANDLE WINAPI CreateServiceA_Hook(
    SC_HANDLE hSCManager,
    LPCSTR lpServiceName,
    LPCSTR lpDisplayName,
    DWORD dwDesiredAccess,
    DWORD dwServiceType,
    DWORD dwStartType,
    DWORD dwErrorControl,
    LPCSTR lpBinaryPathName,
    LPCSTR lpLoadOrderGroup,
    LPDWORD lpdwTagId,
    LPCSTR lpDependencies,
    LPCSTR lpServiceStartName,
    LPCSTR lpPassword
) {
    PreHook(1, "CreateServiceA");
    char buf[600];
    snprintf(buf, 600, "Windows service creation detected.\nService name : %s\nBinary Path : %s\n\nWindows service programs works like a background process which enables malware to persist in your system\nContinue execution?", lpServiceName, lpBinaryPathName);
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_CreateServiceA(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

SC_HANDLE WINAPI CreateServiceW_Hook(
    SC_HANDLE hSCManager,
    LPCWSTR lpServiceName,
    LPCWSTR lpDisplayName,
    DWORD dwDesiredAccess,
    DWORD dwServiceType,
    DWORD dwStartType,
    DWORD dwErrorControl,
    LPCWSTR lpBinaryPathName,
    LPCWSTR lpLoadOrderGroup,
    LPDWORD lpdwTagId,
    LPCWSTR lpDependencies,
    LPCWSTR lpServiceStartName,
    LPCWSTR lpPassword
) {
    PreHook(1, "CreateServiceW");
    char buf[600];
    snprintf(buf, 600, "Windows service creation detected.\nService name : %S\nBinary Path : %S\n\nWindows service programs works like a background process which enables malware to persist in your system\nContinue execution?", lpServiceName, lpBinaryPathName);
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_CreateServiceW(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

INT WINAPI GetLocaleInfoA_Hook(
    LCID Locale,
    LCTYPE LCType,
    LPSTR lpLCData,
    int cchData
) {
    PreHook(1, "GetLocaleInfoA");
    char buf[300];
    snprintf(buf, 300, "This executable is trying to get your device's locale infomation.\nContinue execution?");
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_GetLocaleInfoA(Locale,LCType,lpLCData,cchData);
}

INT WINAPI GetLocaleInfoW_Hook(
    LCID Locale,
    LCTYPE LCType,
    LPWSTR lpLCData,
    int cchData
) {
    PreHook(1, "GetLocaleInfoW");
    char buf[300];
    snprintf(buf, 300, "This executable is trying to get your device's locale infomation.\nContinue execution?");
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_GetLocaleInfoW(Locale,LCType,lpLCData,cchData);
}

INT WINAPI GetLocaleInfoEx_Hook(
    LPCWSTR lpLocaleName,
    LCTYPE LCType,
    LPWSTR lpLCData,
    int cchData
) {
    PreHook(1, "GetLocaleInfoEx");
    char buf[300];
    snprintf(buf, 300, "This executable is trying to get your device's locale infomation.\nContinue execution?");
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_GetLocaleInfoEx(lpLocaleName,LCType,lpLCData,cchData);
}

bool WINAPI CreateTimerQueueTimer_Hook(
    PHANDLE             phNewTimer,
    HANDLE              TimerQueue,
    WAITORTIMERCALLBACK Callback,
    PVOID               Parameter,
    DWORD               DueTime,
    DWORD               Period,
    ULONG               Flags
) {
    PreHook(1, "CreateTimerQueueTimer");
    
    // CreateTimerQueueTimer
    res = MsgBox("Timer creation detected\nTimer is often used in malware to avoid being analyzed in analysis environment.\nIn particular, this delays malicious execution until auto-analysis program finishes its detection.\nContinue execution?");
    if (res == IDNO) 
        ExitProcess(1);
    
    return orig_CreateTimerQueueTimer(phNewTimer, TimerQueue, Callback, Parameter, DueTime, Period, Flags);
}

bool WINAPI SystemParametersInfoA_Hook(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni
) {
    // デスクトップの壁紙変更の検知
    if (uiAction == SPI_SETDESKWALLPAPER) {
        PreHook(2, "SystemParametersInfoA", "SPI_SETDESKWALLPAPER");
        res = MsgBox("Changing desktop wall paper Detected.\nRansomware often changes your wallpaper to show messages to demand ransom.\nContinue execution?");
        if (res == IDNO)
            ExitProcess(1);
    }
    return orig_SystemParametersInfoA(uiAction, uiParam, pvParam, fWinIni);
}

bool WINAPI SystemParametersInfoW_Hook(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni
) {
    // デスクトップの壁紙変更の検知
    if ((uiAction & SPI_SETDESKWALLPAPER) != 0) {
        PreHook(2, "SystemParametersInfoW", "SPI_SETDESKWALLPAPER");
        res = MsgBox("Changing desktop wall paper Detected.\nRansomware often changes your wallpaper to show messages to demand ransom.\nContinue execution?");
        if (res == IDNO)
            ExitProcess(1);
    }
    return orig_SystemParametersInfoW(uiAction, uiParam, pvParam, fWinIni);
}

BOOL WINAPI OpenProcessToken_Hook(
    HANDLE  ProcessHandle,
    DWORD   DesiredAccess,
    PHANDLE TokenHandle
) {
    PreHook(1, "OpenProcessToken");
    res = MsgBox("OpenProcessToken detected.\nThis program is trying to detect its process information such as your Windows username, computer name, and the privilege of this process, which is not common. \nContinue execution if you approve this behavior.");
    if (res == IDNO)
        ExitProcess(1);
    return orig_OpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle);
}

BOOL AdjustTokenPrivileges_Hook(
    HANDLE            TokenHandle,
    BOOL              DisableAllPrivileges,
    PTOKEN_PRIVILEGES NewState,
    DWORD             BufferLength,
    PTOKEN_PRIVILEGES PreviousState,
    PDWORD            ReturnLength
) {
    PreHook(1, "AdjustTokenPrivileges");
    DWORD PrivilegeCount = NewState->PrivilegeCount;
    LUID_AND_ATTRIBUTES* Privileges_arr = NewState->Privileges;

    char privilege_str[300] = {};
    for (UINT i = 0; i < PrivilegeCount; ++i) {
        LPSTR pri_name = new char[300];
        DWORD buf_size = 300;
        if (!LookupPrivilegeNameA(NULL, &(Privileges_arr[i].Luid), pri_name, &buf_size)) {
            res = MsgBox("LookupPrivilegesName failed.");
            char buf[300];
            snprintf(buf, 300, "LookupPrivilegeNameA\nError Code:%u", GetLastError());
            res = MsgBox(buf);
            break;
        }
        strncat_s(privilege_str, pri_name, buf_size);
        strncat_s(privilege_str, "\n", 1);
        delete[] pri_name;
    }
    char buf[500];
    snprintf(buf, 500, "AdjustTokenPrivileges detected.\nThis program is trying to change its privileges.\nHere are the number of requesting privileges: %d\nHere are the requesting privileges: %s\nContinue execution?\n", PrivilegeCount, privilege_str);
    res = MsgBox(buf);
    if (res == IDNO)
        ExitProcess(1);
    return orig_AdjustTokenPrivileges(TokenHandle, DisableAllPrivileges, NewState, BufferLength, PreviousState, ReturnLength);
}

HRESULT WINAPI URLDownloadToFileA_Hook(
    LPUNKNOWN pCaller,
    LPCSTR szURL,
    LPCSTR szFileName,
    _Reserved_ DWORD dwReserved,
    LPBINDSTATUSCALLBACK lpfnCB
) { 
    char msg[1000];
    sprintf_s(msg, "File Downloads detected.\nURL: '%s'.\nFile name: '%s'\nContinue execution?", szURL, szFileName);

    PreHook(3, "URLDownloadToFileA", szURL, szFileName);
    res = MsgBox(msg);
    if (res == IDNO)
        ExitProcess(1);
    return orig_URLDownloadToFileA(pCaller, szURL, szFileName, dwReserved, lpfnCB);

}

HRESULT WINAPI URLDownloadToFileW_Hook(
    LPUNKNOWN pCaller,
    LPCWSTR szURL,
    LPCWSTR szFileName,
    _Reserved_ DWORD dwReserved,
    LPBINDSTATUSCALLBACK lpfnCB
) {
    char msg[1000];
    sprintf_s(msg, "File Downloads detected.\nURL: '%s'.\nFile name: '%s'\nContinue execution?", WStringToString(szURL).c_str(), WStringToString(szFileName).c_str());

    PreHook(3, "URLDownloadToFileW", WStringToString(szURL).c_str(), WStringToString(szFileName).c_str());
    res = MsgBox(msg);
    if (res == IDNO)
        ExitProcess(1);
    return orig_URLDownloadToFileW(pCaller, szURL, szFileName, dwReserved, lpfnCB);

}

// 3: フックする全てのWindowsAPIのリスト
HookList hooklist = {
        HookFunc("kernel32.dll", "SetFileAttributesA", (void**)&orig_SetFileAttributesA, (void*)SetFileAttributesA_Hook),
        HookFunc("kernel32.dll", "SetFileAttributesW", (void**)&orig_SetFileAttributesW, (void*)SetFileAttributesW_Hook),
        HookFunc("kernel32.dll", "IsDebuggerPresent", (void**)&orig_IsDebuggerPresent, (void*)IsDebuggerPresent_Hook),
        HookFunc("kernel32.dll", "CreateProcessA", (void**)&orig_CreateProcessA, (void*)CreateProcessA_Hook),
        HookFunc("kernel32.dll", "CreateProcessW", (void**)&orig_CreateProcessW, (void*)CreateProcessW_Hook),
        HookFunc("ws2_32.dll", "inet_pton", (void**)&orig_inet_pton, (void*)inet_pton_Hook),
        HookFunc("WinInet.dll", "InternetOpenUrlA", (void**)&orig_InternetOpenUrlA, (void*)InternetOpenUrlA_Hook),
        HookFunc("WinInet.dll", "InternetOpenUrlW", (void**)&orig_InternetOpenUrlW, (void*)InternetOpenUrlW_Hook),
        HookFunc("advapi32.dll", "RegCreateKeyExA", (void**)&orig_RegCreateKeyExA, (void*)RegCreateKeyExA_Hook),
        HookFunc("advapi32.dll", "RegCreateKeyExW", (void**)&orig_RegCreateKeyExW, (void*)RegCreateKeyExW_Hook),
        HookFunc("kernel32.dll", "CreateFileA", (void**)&orig_CreateFileA, (void*)CreateFileA_Hook),
        HookFunc("kernel32.dll", "CreateFileW", (void**)&orig_CreateFileW, (void*)CreateFileW_Hook),
        HookFunc("kernel32.dll", "WriteFile", (void**)&orig_WriteFile, (void*)WriteFile_Hook),
        HookFunc("kernel32.dll", "DeleteFileW", (void**)&orig_DeleteFileW, (void*)DeleteFileW_Hook),
        HookFunc("kernel32.dll", "DeleteFileA", (void**)&orig_DeleteFileA, (void*)DeleteFileA_Hook),
        HookFunc("kernel32.dll", "MoveFileA", (void**)&orig_MoveFileA, (void*)MoveFileA_Hook),
        HookFunc("kernel32.dll", "MoveFileW", (void**)&orig_MoveFileW, (void*)MoveFileW_Hook),
        HookFunc("kernel32.dll", "MoveFileExA", (void**)&orig_MoveFileExA, (void*)MoveFileExA_Hook),
        HookFunc("kernel32.dll", "MoveFileExW", (void**)&orig_MoveFileExW, (void*)MoveFileExW_Hook),
        HookFunc("kernel32.dll", "FindFirstFileA", (void**)&orig_FindFirstFileA, (void*)FindFirstFileA_Hook),
        HookFunc("kernel32.dll", "FindNextFileA", (void**)&orig_FindNextFileA, (void*)FindNextFileA_Hook),
        HookFunc("kernel32.dll", "FindFirstFileW", (void**)&orig_FindFirstFileW, (void*)FindFirstFileW_Hook),
        HookFunc("kernel32.dll", "FindNextFileW", (void**)&orig_FindNextFileW, (void*)FindNextFileW_Hook),
        HookFunc("advapi32.dll", "CryptDecrypt", (void**)&orig_CryptDecrypt, (void*)CryptDecrypt_Hook),
        HookFunc("advapi32.dll", "CreateServiceA", (void**)&orig_CreateServiceA, (void*)CreateServiceA_Hook),
        HookFunc("advapi32.dll", "CreateServiceW", (void**)&orig_CreateServiceW, (void*)CreateServiceW_Hook),
        HookFunc("advapi32.dll", "OpenProcessToken", (void**)&orig_OpenProcessToken, (void*)OpenProcessToken_Hook),
        HookFunc("advapi32.dll", "AdjustTokenPrivileges", (void**)&orig_AdjustTokenPrivileges, (void*)AdjustTokenPrivileges_Hook),
        HookFunc("kernel32.dll", "GetLocaleInfoA", (void**)&orig_GetLocaleInfoA, (void*)GetLocaleInfoA_Hook),
        HookFunc("kernel32.dll", "GetLocaleInfoW", (void**)&orig_GetLocaleInfoW, (void*)GetLocaleInfoW_Hook),
        HookFunc("kernel32.dll", "GetLocaleInfoEx", (void**)&orig_GetLocaleInfoEx, (void*)GetLocaleInfoEx_Hook),
        HookFunc("kernel32.dll", "CreateTimerQueueTimer", (void**)&orig_CreateTimerQueueTimer, (void*)CreateTimerQueueTimer_Hook),
        HookFunc("user32.dll", "SystemParametersInfoA", (void**)&orig_SystemParametersInfoA, (void*)SystemParametersInfoA_Hook),
        HookFunc("user32.dll", "SystemParametersInfoW", (void**)&orig_SystemParametersInfoW, (void*)SystemParametersInfoW_Hook),
        HookFunc("urlmon.dll", "URLDownloadToFileA", (void**)&orig_URLDownloadToFileA, (void*)URLDownloadToFileA_Hook),
        HookFunc("urlmon.dll", "URLDownloadToFileW", (void**)&orig_URLDownloadToFileW, (void*)URLDownloadToFileW_Hook)
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