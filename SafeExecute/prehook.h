#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "readmode.h"
#include "mydebug.h"
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

extern char processPath[MAX_PATH];

typedef std::vector<char*> VCHAR;

void LogHookedApi(int argc, VCHAR argv);
void PreHook(int argc, ...);