#include<windows.h>
#include<winbase.h>

int main(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName
) {
    // Move a file to the same place
    MessageBoxA(NULL, "Moving \"MoveFileW.cpp\" to \"MoveFileW2.cpp\" if possible!", "debug", MB_OK);

    LPCWSTR orig = L"./MoveFileW.cpp";
    LPCWSTR dest = L"./MoveFileW2.cpp";
    return MoveFileW(orig, dest);
}