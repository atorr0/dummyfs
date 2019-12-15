/**
 * Module for function call interception (FCI) to cygwin1.dll.
 */

#include <windows.h>
#include <sys/cygwin.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/mount.h>
// #include <unistd.h>

#define LOGCMD(__log_cmd)              \
    printf(__FILE__ ":%u ", __LINE__); \
    __log_cmd;                         \
    printf("\n");                      \
    fflush(stdout);
#define LOG(txt) LOGCMD(printf(txt));

int fci_open(const char *path, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);

    LOGCMD(printf("Opening %s", path));

    int _open = open(path, flags, ap);
    va_end(ap);

    return _open;
}

FILE *fci_fopen(const char *path, const char *mode)
{
    LOGCMD(printf("Opening %s", path));

    return fopen(path, mode);
}

int fci_mount (const char *name, const char *opts, unsigned __flags){

    LOGCMD(printf("Mounting %s [%s] %u", name, opts, __flags));

    // if name starts with "fci:" then hook it, else do default
    // fictional example:  fci:dummyfs:-readonly,-mem=1024
    if (strncmp(name, "fci:", 4) == 0) {
        // TODO update current bash LD_PRELOAD
        return -1; 
    }

    return mount(name, opts, __flags);
}

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
                       IN DWORD nReason,
                       IN LPVOID Reserved)
{
    if (nReason == DLL_PROCESS_ATTACH)
    {
        LOG("compilation (" __DATE__ " " __TIME__ ")");
        LOG("DLL_PROCESS_ATTACH start");

        cygwin_internal(CW_HOOK, "fopen", fci_fopen);
        cygwin_internal(CW_HOOK, "open", fci_open);
        cygwin_internal(CW_HOOK, "mount", fci_mount);
    }
    else if (nReason == DLL_PROCESS_DETACH)
    {
        FreeLibrary(hDllHandle);
    }

    LOGCMD(printf("End (reason=%u)", nReason));

    return TRUE;
}
