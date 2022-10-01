#include <windows.h>
#include <iostream>

int main(void){
    int   ret;
    WCHAR buf[255];

    ret = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SENGCOUNTRY, buf, sizeof(buf)/sizeof(WCHAR));
    MessageBoxW(NULL, buf, L"Your locale", MB_OK);
}