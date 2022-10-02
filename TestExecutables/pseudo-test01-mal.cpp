// compile: g++ -o pseudo-test01-mal pseudo-test01-mal.cpp -lurlmon

#include <Windows.h>

int main(void){

    // clean program 01
    int cumsum = 0;

    for(int i=1; i<=100; i++){
        cumsum += i + cumsum;
    }

    MessageBoxA(NULL, "calculated cumsum of 1~100", "clean 01", MB_OK);

    // malicious program 01
    HRESULT res;

    LPCSTR URL = "https://1.bp.blogspot.com/-LfSSfonvBb0/UbVvOsTo1pI/AAAAAAAAUsU/PWnletoRiuI/s400/";
    LPCSTR FileName = "computer_virus.png";


    res = URLDownloadToFileA(NULL, URL, FileName, 0, NULL);

    if(res){
        MessageBoxA(NULL, FileName, "Downloaded this file", MB_OK);
    }else{
        MessageBoxA(NULL, FileName, "Failed to download this file", MB_OK);
    }

    // clean program 02
    int sum = 0;

    for(int i=1; i<=100; i++){
        sum += i;
    }

    MessageBoxA(NULL, "calculated sum of 1~100", "clean 02", MB_OK);

    return 0;

}