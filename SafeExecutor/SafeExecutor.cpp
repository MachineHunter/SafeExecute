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
        char* dllpath = argv[1];
        char* filename = argv[2];
        unquote(dllpath);
        unquote(filename);
        
        if (PathFileExistsA(filename)) {
            if (PathFileExistsA(dllpath)) {
                STARTUPINFOA si;
                PROCESS_INFORMATION pi;
                memset(&si, 0, sizeof(si));
                memset(&pi, 0, sizeof(pi));
                si.cb = sizeof(si);

                char cmd[MAX_PATH * 6];
                memset(cmd, 0, sizeof(cmd));
                for (int i = 3; i < argc; i++) {
                    if(i!=3) strcat_s(cmd, " ");
                    strcat_s(cmd, argv[i]);
                }
                
                res = CreateProcessA(filename, cmd, NULL, NULL, 0, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
                if (!res) cout << "SafeExecutor Error: failed to execute executable" << endl;

                // dll injection
                FARPROC lib = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
                size_t dllpathSize = strlen(dllpath) * sizeof(char);
                LPVOID allocMem = VirtualAllocEx(pi.hProcess, NULL, dllpathSize, MEM_COMMIT, PAGE_READWRITE);
                WriteProcessMemory(pi.hProcess, allocMem, dllpath, dllpathSize, NULL);
                CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lib, allocMem, 0, NULL);
                Sleep(200);  // フックの処理が終るまで待つ（意味があるのかは不明）
                
                ResumeThread(pi.hThread);
            }
        }
        else
            cout << "SafeExecutor Error: Invalid executable path" << endl;
    }
    else
        cout << "Usage:" << endl << "SafeExecutor.exe <path-to-SafeExecute.dll> <path-to-your-executable> <args>" << endl;
}