#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "mydebug.h"
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

extern char processPath[MAX_PATH];

void PreHook(int argc, ...);