#pragma once
#include <iostream>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

extern char processPath[MAX_PATH];

// 全フック関数の冒頭で呼ばれる共通の処理
void PreHook(LPCSTR apiName);