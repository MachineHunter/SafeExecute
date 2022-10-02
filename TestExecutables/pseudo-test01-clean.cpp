#include <Windows.h>

int main(void){

    int cumsum = 0;

    for(int i=1; i<=100; i++){
        cumsum += i + cumsum;
    }

    MessageBoxA(NULL, "calculated cumsum of 1~100", "clean 01", MB_OK);

    int sum = 0;

    for(int i=1; i<=100; i++){
        sum += i;
    }

    MessageBoxA(NULL, "calculated sum of 1~100", "clean 01", MB_OK);

    return 0;

}