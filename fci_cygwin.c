/**
 * Module for function call interception (FCI) to cygwin1.dll.
 */

#include <windows.h>

int _printf(char *str, ...)
{

    HANDLE std_out;
    int i;
    char *error_msg;

    std_out = GetStdHandle(STD_OUTPUT_HANDLE);

    if (std_out == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, "stdout not available", "Error", MB_OK);
        return 1;
    }

    DWORD nocw;
    if (!WriteConsole(std_out, str, strlen(str), &nocw, NULL))
    {
        MessageBox(NULL, "WriteConsole error", "Error", MB_OK);
        return 2;
    }

    return 0;
}

#define LOGCMD(cmd)                _printf(__FILE__ ":" __LINE__);(cmd);                         _printf("\n");
#define LOG(text) _printf(text)

typedef void (*ErrorHandler)(char *, ...);

int _initPAPointers(HMODULE);

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

    _printf("getProcAddress4(%s): %p\n", lpProcName, pointer);
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

        // char *n;
        // sprintf(n, "c:\\cygwin\\bin\\%s", name);

        // h = LoadLibrary(n);
    }

    _printf("LoadLibrary(%s): %p\n", name, h);

    return h;
}

ErrorHandler printErrorHandler(char *str)
{
    _printf("ErrorHandler: ");
    _printf(str);
    _printf("\n");
}

HMODULE c2dll;

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
                       IN DWORD nReason,
                       IN LPVOID Reserved)
{
    LOG("compilation (" __DATE__ " " __TIME__ ")");
    _printf("%u", nReason);

    if (nReason == DLL_PROCESS_ATTACH)
    {

        LOG("DLL_PROCESS_ATTACH start");

        // _printf("fopen() points to: %p\n", fopen);

        if (!(c2dll = findLoadLibrary("cygwin2.dll")))
            return FALSE;

        // call to cygwin-stub.h:_initPAPointers()
        if (!_initPAPointers(c2dll))
            return FALSE;

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

        // fflush(stdout);

        LOG("DLL_PROCESS_ATTACH end");
    }
    else if (nReason == DLL_PROCESS_DETACH)
    {
        FreeLibrary(hDllHandle);
    }

    return TRUE;
}
