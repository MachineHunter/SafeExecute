#include <windows.h>

int main(void){
    int   ret;
    char buf[300];

    ret = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SENGCOUNTRY, buf, 255);
    MessageBoxA(NULL, buf, "Your locale", MB_OK);
}