// ファイル:CreateDeleteFileW_test.txtをCurrent Directryに作成し，削除するプログラム

#include <Windows.h>

int main(void){

    LPCWSTR create_file_name = L"./TestExecutables/CreateDeleteFileW_test.txt";
    
    bool res = CreateFileW(
                    create_file_name,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_DELETE,
                    NULL,
                    CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    
    // check if the file was created
    if(res){
        MessageBoxW(NULL, create_file_name, L"Create File", MB_OK);
    }else{
        MessageBoxW(NULL, create_file_name, L"The file already exists", MB_OK);
    }
    
    res = DeleteFileW(create_file_name);

    // check if the file was deleted
    if (res){
        MessageBoxW(NULL, create_file_name, L"Delete File", MB_OK);
    }else{
        MessageBoxW(NULL, create_file_name, L"Failed to delete", MB_OK);
    }

    return 0;

}