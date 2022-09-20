#include<windows.h>
#include<winbase.h>

int main(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName
) {
    // Move a file to the same place
    MessageBoxA(NULL, "Moving \"MoveFile.cpp\" to \"MoveFile.cpp\"", "debug", MB_OK);

    LPCWSTR orig = L"./MoveFile.cpp";
    LPCWSTR dest = L"./MoveFile.cpp";
    return MoveFile(orig, dest);
}