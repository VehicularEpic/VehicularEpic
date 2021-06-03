#ifdef _MSC_VER

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <delayimp.h>

#include <cstring>

static FARPROC WINAPI NodeDelayLoadHook(unsigned int event, DelayLoadInfo *info) {
    if (event != dliNotePreLoadLibrary)
        return nullptr;

    if (_stricmp(info->szDll, "NODE.EXE") != 0)
        return nullptr;

    return (FARPROC) GetModuleHandle(nullptr);
}

decltype(__pfnDliNotifyHook2) __pfnDliNotifyHook2 = NodeDelayLoadHook;

#endif
