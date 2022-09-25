#include <windows.h>
#include <winbase.h>

int main(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName,
    DWORD  dwFlags
) {
    // Move a file to the same place
    MessageBoxA(NULL, "Moving \"MoveFileExW.cpp\" to \"MoveFileExW.cpp\"", "debug", MB_OK);

    LPCWSTR orig = L"./MoveFileExW.cpp";
    LPCWSTR dest = L"./MoveFileExW.cpp";
    return MoveFileExW(orig, dest, MOVEFILE_REPLACE_EXISTING);
}