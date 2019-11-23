#include <windows.h>
#pragma pack(1)

HINSTANCE hLThis = 0;
HINSTANCE hL = 0;

// __HANDLE_NAMES__
FARPROC printf_real;

BOOLEAN WINAPI DllMain( HINSTANCE hDllHandle, 
         DWORD     nReason, 
         LPVOID    reserved1)
{
    if (nReason == DLL_PROCESS_ATTACH)
    {
        hLThis = hDllHandle;
        hL = LoadLibrary("cygwin1.dll");
        if (!hL) return TRUE;

        // __INITIALIZE_HANDLES__
printf_real = GetProcAddress(hL,"printf");
    }
    else if (nReason == DLL_PROCESS_DETACH)
    {
        FreeLibrary(hL);
    }
    return TRUE;
}

// __FUNCTION_BODIES__
extern __declspec(naked) void printf () { __asm ("jmp %0;": /* No outputs. */ : "p" (printf_real) ); }
