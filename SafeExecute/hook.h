#pragma once
#include <vector>
#include "mydebug.h"
#include "prehook.h"
#include <WinSock2.h>
#include "ordinals.h"
#include <Dbghelp.h>
#pragma comment(lib, "Dbghelp")

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

    HookFunc(const char* _dllname, const char* _funcname, void** _origfunc, void* _hook) {
        dllname = _dllname;
        func.name = _funcname;
        origfunc = _origfunc;
        hook = _hook;
        isOrdinal = false;
    }

    HookFunc(const char* _dllname, DWORD _ordinal, void** _origfunc, void* _hook) {
        dllname = _dllname;
        func.ordinal = _ordinal;
        origfunc = _origfunc;
        hook = _hook;
        isOrdinal = true;
    }
};
typedef std::vector<HookFunc> HookList;

void Hook();