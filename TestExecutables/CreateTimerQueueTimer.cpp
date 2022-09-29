#include <iostream>
#include <windows.h>
#include <stdio.h>

HANDLE hTimerQueue = NULL;
HANDLE hTimer = NULL;

// CallBack関数
VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
    printf("");
}

int main()
{
    
    // プログラム開始時に一回タイマーキューを作成
    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        printf("CreateTimerQueue failed (%d)\n", GetLastError());
        return -1;
    }

    // タイマーを10回作成する
    for (int i = 0; i < 10; i++){
        // すでにタイマがかかっていたら一度タイマ削除する(メモリリークを防ぐ)
        if (hTimerQueue != NULL && hTimer != NULL)
        {
            if (!DeleteTimerQueueTimer(hTimerQueue, hTimer, NULL))
            {
                printf("DeleteTimerQueueTimer failed (%d)\n", GetLastError());
                return -3;
            }
            else
            {
                hTimer = NULL;
            }
        }

        // タイマースタート
        if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
            (WAITORTIMERCALLBACK)TimerRoutine, NULL, 1, 0, 0))
        {
            printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
            return -2;
        }

        Sleep(50);
        
    }

    return 0;
}
