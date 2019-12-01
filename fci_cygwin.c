/**
 * Module for function call interception (FCI) to cygwin1.dll.
 */

#include <windows.h>
#include <stdio.h>
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

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
                       IN DWORD nReason,
                       IN LPVOID Reserved)
{

    LOG("compilation (" __DATE__ " " __TIME__ ")");
    LOGCMD(printf("%u", nReason));

    if (nReason == DLL_PROCESS_ATTACH)
    {

        LOG("DLL_PROCESS_ATTACH start");

        cygwin_internal(CW_HOOK, "fopen", fci_fopen);

        LOG("DLL_PROCESS_ATTACH end");
    }
    else if (nReason == DLL_PROCESS_DETACH)
    {
        FreeLibrary(hDllHandle);
    }

    return TRUE;
}
