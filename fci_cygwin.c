/**
 * Module for function call interception (FCI) to cygwin1.dll.
 */

#include <windows.h>
#include <sys/cygwin.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
// #include <sys/mount.h>
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

    LOGCMD(printf("Opening %s with flags %d", path, flags));

    int _open = open(path, flags, ap);
    va_end(ap);

    return _open;
}

FILE *fci_fopen(const char *path, const char *mode)
{
    LOGCMD(printf("Opening %s with mode %s", path, mode));

    return fopen(path, mode);
}

static void
__attribute__((constructor)) 
fci_init(void)
{
    LOG("compilation (" __DATE__ " " __TIME__ ")");
    LOG("fci_init");

    cygwin_internal(CW_HOOK, "fopen", fci_fopen);
    cygwin_internal(CW_HOOK, "open", fci_open);
}
