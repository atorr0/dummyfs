#include <stdio.h>
#include <windows.h>

#define LOG(text) fprintf(stdout, __DATE__ " " __TIME__ " %s:%d  " text "\n", __FILE__, __LINE__)

static void
__attribute__((constructor)) 
hook_init(void)
{
    LOG("hook_init");
    // fprintf(stdout, "printf: %016x %016x %016x\n", printf, &printf, *printf);
    // fprintf(stdout, "hooked_printf: %016x %016x %016x\n", hooked_printf, &hooked_printf, *hooked_printf);
    // int (*ptr)() = printf;
    // fprintf(stdout, "ptr: %016x %016x %016x\n", ptr, &ptr, *ptr);

    PFN_HELLO fnHello;
    HMODULE hLib, h = LoadLibrary(TEXT("cygwin1.dll")); 
    PFN_CYGWIN_DLL_INIT init = (PFN_CYGWIN_DLL_INIT) GetProcAddress(h,"cygwin_dll_init");
    init(); 

    hLib = LoadLibrary (TEXT("C:\\cygwin\\home\\Oleg\\mydll.dll"));
    fnHello = (PFN_HELLO) GetProcAddress (hLib, "hello");
    return fnHello();
}

BOOLEAN WINAPI DllMain( IN HINSTANCE hDllHandle, 
         IN DWORD     nReason, 
         IN LPVOID    Reserved )
 {
    LOG("DllMain");
    printf("nReason: %lu\n", nReason);

    return TRUE;
 }

int hooked_printf(const char *__restrict _Format, ...)
{

    hook_init();
    LOG("xxx");

    return 0;
}
