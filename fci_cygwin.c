/**
 * Module for function call interception (FCI) to cygwin1.dll.
 */

#define _GNU_SOURCE

#include <windows.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/cygwin.h>

#define LOGCMD(__log_cmd)              \
    printf(__FILE__ ":%u ", __LINE__); \
    __log_cmd;                         \
    printf("\n");                      \
    fflush(stdout);
#define LOG(txt) LOGCMD(printf(txt));

FILE *fci_fopen(const char *path, const char *mode)
{
    LOGCMD(printf("Opening %s", path));

    return fopen(path, mode);
}

int _initPAPointers(HMODULE);

HMODULE findLoadLibrary(const char *name)
{
    HMODULE h;

    if (!(h = LoadLibrary(name)))
    {

        LOG("Retry 1");

        char *n = 0;
        sprintf(n, "c:\\cygwin\\bin\\%s", name);

        h = LoadLibrary(n);
    }

    printf("LoadLibrary(%s): %p\n", name, h);

    return h;
}

HMODULE c2dll;

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
                       IN DWORD nReason,
                       IN LPVOID Reserved)
{

    LOG("compilation (" __DATE__ " " __TIME__ ")");
    LOGCMD(printf("%u", nReason));

    if (nReason == DLL_PROCESS_ATTACH)
    {

        LOG("DLL_PROCESS_ATTACH start");

        // printf("fopen() points to: %p\n", fopen);

        // if (!(c2dll = findLoadLibrary("cygwin2.dll")))
        //     return FALSE;

        // call to cygwin-stub.h:_initPAPointers()
        if (!_initPAPointers(c2dll))
            return FALSE;

        cygwin_internal(CW_HOOK, "fopen", fci_fopen);

        LOG("DLL_PROCESS_ATTACH end");
    }
    else if (nReason == DLL_PROCESS_DETACH)
    {
        FreeLibrary(hDllHandle);
    }

    return TRUE;
}

int _initPAPointers(HMODULE hModul)
{
    return TRUE;
}