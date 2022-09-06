#include "pch.h"
#include "mydebug.h"

void DbgPrint(const char* fmt, ...) {
    char buf[256];
    va_list v1;
    va_start(v1, fmt);
    vsnprintf(buf, sizeof(buf), fmt, v1);
    va_end(v1);
    OutputDebugStringA(buf);
}