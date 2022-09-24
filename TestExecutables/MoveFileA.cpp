#include<windows.h>
#include<winbase.h>

int main(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName
) {
    // Move a file to the same place
    MessageBoxA(NULL, "Moving \"MoveFileA.cpp\" to \"MoveFileA2.cpp\" if possible!", "debug", MB_OK);

    LPCSTR orig = "./MoveFileA.cpp";
    LPCSTR dest = "./MoveFileA2.cpp";
    return MoveFileA(orig, dest);
}