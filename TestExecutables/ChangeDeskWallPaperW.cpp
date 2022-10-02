// デスクトップの壁紙を変更するテストコード
#include <Windows.h>
#include <string>


int main(void){

    bool ret;
    wchar_t* file_name = L"blackwallpaper.PNG";

    ret = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, file_name,SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

    if(ret){
        MessageBoxW(NULL, file_name, L"Changed desktop wall paper", MB_OK);
    }else{
        MessageBoxW(NULL, file_name, L"Failed to change desktop wall paper", MB_OK);
    }
}
