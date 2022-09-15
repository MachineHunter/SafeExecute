#pragma once
#include <vector>
#include "mydebug.h"
#include "prehook.h"
#include <Dbghelp.h>
#pragma comment(lib, "Dbghelp")

extern char processPath[MAX_PATH];

typedef struct HookFunc {
    const char* dllname;
    const char* funcname;
    void** origfunc;
    void* hook;

    HookFunc(const char *_dllname, const char *_funcname, void** _origfunc, void* _hook)
        : dllname(_dllname), funcname(_funcname), origfunc(_origfunc), hook(_hook) {};
};
typedef std::vector<HookFunc> HookList;

void Hook();