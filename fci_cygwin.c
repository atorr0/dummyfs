/**
 * Module for function call interception (FCI) to cygwin1.dll.
 */

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
// int printf(char *, ...);
// int fflush(void *);
// void *stdout;

#define LOGCMD(cmd)                        \
    printf("%s:%d  ", __FILE__, __LINE__); \
    (cmd);                                 \
    printf("\n");                          \
    fflush(stdout);
#define LOG(text) LOGCMD(printf(text))

typedef void (*ErrorHandler)(char *, ...);

/**
 * Calls GetProcAddress and validate it's not null.
 * 
 * @param 
 * @return Handle
 */
int getProcAddress4(HMODULE hModule, LPCSTR lpProcName, FARPROC *pFarproc, ErrorHandler errorHandler)
{

    FARPROC pointer = GetProcAddress(hModule, lpProcName);

    if (!pointer)
        errorHandler("getProcAddress4(%s): NULL", lpProcName);

    *pFarproc = pointer;

    LOGCMD(printf("getProcAddress4(%s): %p\n", lpProcName, pointer));
}

// __stdcall int _dll_puts(const char *str);
// asm(
//     ".global _dll_puts                             \n\t"
//     "_dll_puts:                                    \n\t"
//     "       jmp *_proc_puts                     \n\t" //
// );

// __stdcall int epilogue()
// {
//     LOG("epilogue hit");
// }

// __stdcall int indirect_puts(const char *str);
// asm(
//     ".global indirect_puts                             \n\t"
//     "indirect_puts:                                    \n\t"
//     "       jmp puts                                   \n\t" //
// );

HMODULE findLoadLibrary(const char *name)
{

    HMODULE h;

    if (!(h = LoadLibrary(name)))
    {

        LOG("Retry 1");

        char *n;
        sprintf(n, "c:\\cygwin\\bin\\%s", name);

        h = LoadLibrary(n);
    }

    LOGCMD(printf("LoadLibrary(%s): %p\n", name, h));

    return h;
}

ErrorHandler printErrorHandler(char *str)
{
    printf("ErrorHandler: ");
    printf(str);
    printf("\n");
}

FILE *my_fopen(char *name, char*type) {
    printf("my_fopen called!\n");
}

BOOLEAN WINAPI DllMain( IN HINSTANCE hDllHandle, 
         IN DWORD     nReason, 
         IN LPVOID    Reserved )
{
    LOG( __FILE__ " compilation (" __DATE__ " " __TIME__ ")");

    LOGCMD(printf("%u", nReason))

    if (nReason != DLL_PROCESS_ATTACH) return TRUE;

    printf("fopen() points to: %p\n", fopen);
    printf("my_fopen() points to: %p\n", my_fopen);

    // puts("normal puts");

    // fflush(stdout);

    // indirect_puts("indirect_puts");

    // fflush(stdout);

    // if (!(hdll = findLoadLibrary("cygwin1.dll")))
    //     return 1;

    // // void (*cygwin_dll_init)() = GetProcAddress(hdll, "cygwin_dll_init");
    // FARPROC GET_PROC_ADDRESS_OR_RETURN(cygwin_dll_init, "cygwin_dll_init");
    // cygwin_dll_init();

    // LOG("init called");

    // // indirect_puts("indirect_puts");

    // int (*_proc_puts2)(const char *, ...) = GET_PROC_ADDRESS_OR_RETURN(_proc_puts2, "printf");

    // LOG("GetProcAddress called");

    // _proc_puts2("hola");

    // fflush(stdout);

    // FARPROC GET_PROC_ADDRESS_OR_RETURN(_proc_printf, "printf");

    // _proc_printf("_proc_printf");

    // fflush(stdout);

    // // GET_PROC_ADDRESS_OR_RETURN(_proc_puts, "puts");
    // // printf("_proc_puts: %p %p\n", _proc_puts, &_proc_puts);
    // // _proc_puts("_proc_puts");

    // // _proc_puts= 0x18019e030;

    // // _proc_puts("_proc_puts2");

    // LOG("end");
    // return 0;

    // printf("puts: %p %p\n", puts, &puts);
    // printf("_proc_puts: %p %p\n", _proc_puts, &_proc_puts);
    // printf("_dll_puts: %p %p\n", _dll_puts, &_dll_puts);

    // fflush(stdout);

    // _dll_puts("XAXA");

    // puts("YYY");

    fflush(stdout);

    LOG("end");

    return TRUE;
}
