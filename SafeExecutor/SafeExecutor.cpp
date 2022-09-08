#include <iostream>
#include <Windows.h>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

using namespace std;

int main(int argc, char* argv[]) {
    BOOL res;

    if (argc > 2) {
        char* dllpath  = argv[1];
        char* filename = argv[2];

        if (PathFileExistsA(filename)) {
            if (PathFileExistsA(dllpath)) {
                STARTUPINFOA si;
                PROCESS_INFORMATION pi;
                memset(&si, 0, sizeof(si));
                memset(&pi, 0, sizeof(pi));
                si.cb = sizeof(si);

                char cmd[MAX_PATH * 6];
                memset(cmd, 0, sizeof(cmd));
                strcat_s(cmd, filename);
                for (int i = 3; i < argc; i++) {
                    strcat_s(cmd, " ");
                    strcat_s(cmd, argv[i]);
                }

                res = CreateProcessA(NULL, cmd, NULL, NULL, 0, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
                if (!res) cout << "Error: failed to execute executable" << endl;

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
            cout << "Error: Invalid executable path" << endl;
    }
    else
        cout << "Usage:" << endl << "SafeExecutor.exe <path-to-SafeExecute.dll> <path-to-your-executable> <args>" << endl;
}