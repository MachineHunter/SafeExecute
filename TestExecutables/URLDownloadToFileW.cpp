// URLを指定してファイルをダウンロードするテストコード
// compile:  g++ -o URLDownloadToFileW URLDownloadToFileW.cpp -lurlmon 

#include <Windows.h>


int main(void){

    HRESULT res;

    LPCWSTR URL = L"https://1.bp.blogspot.com/-LfSSfonvBb0/UbVvOsTo1pI/AAAAAAAAUsU/PWnletoRiuI/s400/";
    LPCWSTR FileName = L"computer_virus.png";


    res = URLDownloadToFileW(NULL, URL, FileName, 0, NULL);

    if(res){
        MessageBoxW(NULL, FileName, L"Downloaded this file", MB_OK);
    }else{
        MessageBoxW(NULL, FileName, L"Failed to download this file", MB_OK);
    }

    return 0;
}
