// ファイル:CreateDeleteFileW_test.txtをCurrent Directryに作成し，削除するプログラム

#include <Windows.h>

int main(void){

    LPCSTR create_file_name = "./TestExecutables/CreateDeleteFileW_test.txt";
    
    bool res = CreateFileA(
                    create_file_name,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_DELETE,
                    NULL,
                    CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    
    // check if the file was created
    if(res){
        MessageBoxA(NULL, create_file_name, "Create File", MB_OK);
    }else{
        MessageBoxA(NULL, create_file_name, "The file already exists", MB_OK);
    }
    
    res = DeleteFileW((LPCWSTR)create_file_name);

    // check if the file was deleted
    if (res){
        MessageBoxA(NULL, create_file_name, "Delete File", MB_OK);
    }else{
        MessageBoxA(NULL, create_file_name, "Failed to delete", MB_OK);
    }

    return 0;

}