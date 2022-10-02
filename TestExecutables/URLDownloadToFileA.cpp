// URLを指定してファイルをダウンロードするテストコード
// compile:  g++ -o URLDownloadToFileA URLDownloadToFileA.cpp -lurlmon 

#include <Windows.h>


int main(void){

    HRESULT res;

    LPCSTR URL = "https://1.bp.blogspot.com/-LfSSfonvBb0/UbVvOsTo1pI/AAAAAAAAUsU/PWnletoRiuI/s400/";
    LPCSTR FileName = "computer_virus.png";


    res = URLDownloadToFileA(NULL, URL, FileName, 0, NULL);

    if(res){
        MessageBoxA(NULL, FileName, "Downloaded this file", MB_OK);
    }else{
        MessageBoxA(NULL, FileName, "Failed to download this file", MB_OK);
    }

    return 0;
}
