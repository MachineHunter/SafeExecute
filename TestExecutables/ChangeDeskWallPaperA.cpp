// デスクトップの壁紙を変更するテストコード
#include <Windows.h>

int main(void){

    bool ret;
    char* file_name = "blackwallpaper.PNG";

    ret = SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, file_name,SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

    if(ret){
        MessageBoxA(NULL, file_name, "Changed desktop wall paper", MB_OK);
    }else{
        MessageBoxA(NULL, file_name, "Failed to change desktop wall paper", MB_OK);
    }
}
