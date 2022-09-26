#include<windows.h>
#include<winbase.h>

int main(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName
) {
    // Move a file to the same place
    MessageBoxA(NULL, "Moving \"MoveFileA.cpp\" to \"MoveFileA2.cpp\" if possible!", "debug", MB_OK);

    LPCTSTR orig = "./MoveFileA.cpp";
    LPCTSTR dest = "./MoveFileA2.cpp";
    return MoveFileA(orig, dest);
}