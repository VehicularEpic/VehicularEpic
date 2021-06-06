#ifdef _MSC_VER

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <delayimp.h>

#include <cstdio>
#include <cstring>

static void reopen(FILE *stream, const char *mode) {
    freopen_s(&stream, "CON", mode, stream);
}

static FARPROC WINAPI NodeDelayLoadHook(unsigned int event, DelayLoadInfo *info) {
    if (event != dliNotePreLoadLibrary)
        return nullptr;

    if (_stricmp(info->szDll, "NODE.EXE") != 0)
        return nullptr;

    AttachConsole(ATTACH_PARENT_PROCESS);

    reopen(stdin, "r");
    reopen(stdout, "w");
    reopen(stderr, "w");

    return (FARPROC) GetModuleHandle(nullptr);
}

decltype(__pfnDliNotifyHook2) __pfnDliNotifyHook2 = NodeDelayLoadHook;

#endif
