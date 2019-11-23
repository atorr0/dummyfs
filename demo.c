#include <windows.h>
#include <stdio.h>

#define LOG(text) printf(__DATE__ " " __TIME__ " %s:%d  " text "\n", __FILE__ , __LINE__)

#define call(f) \
    __asm__ volatile ("callq *%0;" : : "g" (f) : "cc", "memory")

#define jmp(f) \
     __asm__ volatile ("jmp puts;" : : : "cc", "memory")


__stdcall
int indirect_puts(const char* str);

asm                                                                              
(                                                                                
".global indirect_puts                             \n\t"                                    
"indirect_puts:                                    \n\t"
"       jmp puts                              \n\t"                                    
);                                                                               


int main() {

    LOG("main");

    puts("normal puts");

    fflush(stdout);

    indirect_puts("indirect_puts");

    fflush(stdout);

    LOG("end");

    return 0;

    // HANDLE hdll = LoadLibrary("cygwin_proxy.dll");

    // if (!hdll) {
    //     LOG("hdll null");
    //     return 1;
    // }
    // printf("hdll: %016x %016x\n", hdll, &hdll);

    // FARPROC hooked_printf = hooked_printf = GetProcAddress(hdll, "printf");

    // if (!hooked_printf) {
    //     LOG("hooked_printf null");
    //     return 2;
    // }
    // printf("hooked_printf: %016x %016x\n", hooked_printf, &hooked_printf);

    // hooked_printf("hooked_printf");

    // LOG("SUCCESS!");

    // // hooked_printf("hooked_printf: %016x %016x %016x\n", hooked_printf, &hooked_printf, *hooked_printf);

    // // fprintf(stdout, "printf: %016x %016x %016x\n", printf, &printf, *printf);

    // return 0;
}