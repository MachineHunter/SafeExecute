#pragma once
#include <fstream>
#include <iostream>
#include "mydebug.h"
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#define MODE_NORMAL 0
#define MODE_ERRORDISPLAY 1
#define MODE_INTERACTIVE 2

extern char processPath[MAX_PATH];
extern DWORD MODE;

using namespace std;

void ReadMode();