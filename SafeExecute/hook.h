#pragma once
#include <vector>
#include "mydebug.h"
#include "prehook.h"
#include <WinSock2.h>
#include "ordinals.h"
#include <Dbghelp.h>
#include <Wincrypt.h>
#include <processthreadsapi.h>
#pragma comment(lib, "Dbghelp")
#pragma comment(lib, "crypt32.lib")

#define MsgBox(X) MessageBoxA(NULL, X, "SafeExecute", MB_YESNO)

extern char processPath[MAX_PATH];

typedef struct HookFunc {
    const char* dllname;
    union {
        const char* name;
        DWORD ordinal;
    } func;
    void** origfunc;
    void* hook;
    bool isOrdinal;
    bool isChecked;

    HookFunc(const char* _dllname, const char* _funcname, void** _origfunc, void* _hook) {
        dllname = _dllname;
        func.name = _funcname;
        origfunc = _origfunc;
        hook = _hook;
        isOrdinal = false;
        isChecked = true; // TODO: デプロイ時はfalseに
    }

    HookFunc(const char* _dllname, DWORD _ordinal, void** _origfunc, void* _hook) {
        dllname = _dllname;
        func.ordinal = _ordinal;
        origfunc = _origfunc;
        hook = _hook;
        isOrdinal = true;
        isChecked = true; // TODO: デプロイ時はfalseに
    }
};
typedef std::vector<HookFunc> HookList;
extern HookList hooklist;

void Hook();

std::string WStringToString(const std::wstring& s);