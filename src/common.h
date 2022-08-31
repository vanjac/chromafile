#pragma once

// win32
#ifndef UNICODE
#define UNICODE
#endif
#define STRICT
#define WIN32_LEAN_AND_MEAN
// target Windows 7
// https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601


#ifdef CHROMAFILE_DEBUG
#define debugPrintf wprintf
// use checkHR instead of SUCCEEDED when you expect the call to succeed
#define checkHR(hr) logHRESULT((hr), __FILE__, __LINE__, #hr)
bool logHRESULT(long hr, const char *file, int line, const char *expr);
#define checkLE(expr) checkLETemplate((expr), __FILE__, __LINE__, #expr)
void logLastError(const char *file, int line, const char *expr);
template <typename T>
T checkLETemplate(T result, const char *file, int line, const char *expr) {
    if (!result)
        logLastError(file, line, expr);
    return result;
}
#else
#define debugPrintf(...)
#define checkHR SUCCEEDED
#define checkLE(expr) (expr)
#endif

#ifdef CHROMAFILE_MEMLEAKS
// https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
