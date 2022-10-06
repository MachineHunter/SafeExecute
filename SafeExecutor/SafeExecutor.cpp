#include <iostream>
#include <Windows.h>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

using namespace std;

void unquote(char* s) {
    if (s[0] == '\'' || s[0] == '\"') {
        s = s + 1;
        s[strlen(s) - 1] = '\0';
    }
}

int main(int argc, char* argv[]) {
    BOOL res;

    if (argc > 2) {
        char dllpath[MAX_PATH * 2];
        memset(dllpath, 0, MAX_PATH * 2);
        strcpy_s(dllpath, argv[1]);
        char* filename = argv[2];
        unquote(filename);
        
        unquote(dllpath);
        for (int i = 0; i < 3; i++) PathRemoveFileSpecA(dllpath);
        strcat_s(dllpath, "\\Packages\\4c089c08-edd9-4511-b58f-adb16c064298_s08gjkwpj9ncj\\LocalCache\\Local\\安全実行侍～俺を信じろ～\\bin");
        
        MessageBoxA(NULL, filename, "safeexecutor debug", MB_OK);
        if (PathFileExistsA(filename)) {
            MessageBoxA(NULL, dllpath, "safeexecutor debug", MB_OK);
            if (PathFileExistsA(dllpath)) {
                STARTUPINFOA si;
                PROCESS_INFORMATION pi;
                memset(&si, 0, sizeof(si));
                memset(&pi, 0, sizeof(pi));
                si.cb = sizeof(si);

                char cmd[MAX_PATH * 6];
                memset(cmd, 0, sizeof(cmd));
                // strcat_s(cmd, filename);
                for (int i = 3; i < argc; i++) {
                    if(i!=3) strcat_s(cmd, " ");
                    strcat_s(cmd, argv[i]);
                }
                
                MessageBoxA(NULL, filename, "executor debug", MB_OK);
                MessageBoxA(NULL, cmd, "executor debug", MB_OK);
                res = CreateProcessA(filename, cmd, NULL, NULL, 0, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
                if (!res) cout << "SafeExecutor Error: failed to execute executable" << endl;
                MessageBoxA(NULL, "shit", "executor debug", MB_OK);

                // dll injection
                FARPROC lib = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
                if(lib==NULL) MessageBoxA(NULL, "GetProcAddress failed", "executor debug", MB_OK);
                size_t dllpathSize = strlen(dllpath) * sizeof(char);
                LPVOID allocMem = VirtualAllocEx(pi.hProcess, NULL, dllpathSize, MEM_COMMIT, PAGE_READWRITE);
                if (allocMem == NULL) MessageBoxA(NULL, "VirtualAllocEx failed", "executor debug", MB_OK);
                BOOL aaa = WriteProcessMemory(pi.hProcess, allocMem, dllpath, dllpathSize, NULL);
                if (aaa == 0) MessageBoxA(NULL, "WriteProcessMemory failed", "executor debug", MB_OK);

                HANDLE bbb = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lib, allocMem, 0, NULL);
                if(bbb==NULL) MessageBoxA(NULL, "CreateRemoteThreada failed", "executor debug", MB_OK);
                Sleep(200);  // フックの処理が終るまで待つ（意味があるのかは不明）
                
                DWORD ccc = ResumeThread(pi.hThread);
                if(ccc==-1) MessageBoxA(NULL, "resume failed", "executor debug", MB_OK);
            }
        }
        else
            cout << "SafeExecutor Error: Invalid executable path" << endl;
    }
    else
        cout << "Usage:" << endl << "SafeExecutor.exe <path-to-SafeExecute.dll> <path-to-your-executable> <args>" << endl;
}