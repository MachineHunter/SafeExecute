#pragma once
#include <iostream>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

extern char processPath[MAX_PATH];

// �S�t�b�N�֐��̖`���ŌĂ΂�鋤�ʂ̏���
void PreHook(LPCSTR apiName);