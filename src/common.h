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


#ifdef CHROMABROWSE_DEBUG
#define debugPrintf wprintf
#else
#define debugPrintf(...)
#endif
