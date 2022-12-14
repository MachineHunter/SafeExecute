#include <windows.h>
#include <winbase.h>

int main(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName,
    DWORD  dwFlags
) {
    // Move a file to the same place
    MessageBoxA(NULL, "Moving \"MoveFileExA.cpp\" to \"MoveFileExA.cpp\"", "debug", MB_OK);

    LPCSTR orig = "./MoveFileExA.cpp";
    LPCSTR dest = "./MoveFileExA.cpp";
    return MoveFileExA(orig, dest, MOVEFILE_REPLACE_EXISTING);
}