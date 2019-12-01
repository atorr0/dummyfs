# dummyfs
A dummy FS for Cygwin

## Current status

**2019-12-01**
Changed to LD_PRELOAD + cygwin_internal(CW_HOOK,...) way of hooking.
The initial demo of fopen-ing prints a successful message.

**2019-11-23**
The `demo.c` can make a JMP-based call to `puts` function.


## Information links

### C

* https://www.tutorialspoint.com/c_standard_library/c_function_puts.htm
* https://stackoverflow.com/questions/28923106/how-can-i-write-in-gnu-c-a-proxy-function-to-interface-two-different-calling-c
* https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/calling-convention
* https://barrgroup.com/Embedded-Systems/How-To/C-Volatile-Keyword
* https://www.researchgate.net/publication/327861541_Compile-Time_Function_Call_Interception_to_Mock_Functions_in_CC
* http://www.gotw.ca/gotw/057.htm
* https://bytes.com/topic/c/answers/876132-how-override-standard-printf-defined-gcc-library
* https://stackoverflow.com/questions/7278234/why-doesnt-gcc-support-naked-functions
* https://stackoverflow.com/questions/53407795/how-to-write-asm-goto-inline-assembly

#### GCC/gas

* https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html#Option-Summary
* https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
* https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html#Simple-Constraints
* https://sourceware.org/binutils/docs/as/i386_002dVariations.html#i386_002dVariations
* https://sourceware.org/binutils/docs/as/BPF-Opcodes.html#Jump-instructions

#### dlopen/LoadLibrary/DLL

* https://www.codeproject.com/Articles/16541/Create-your-Proxy-DLLs-automatically
* https://linux.die.net/man/3/dlopen
* https://stackoverflow.com/questions/45041751/cygwin-dlopen-error-invalid-or-incomplete-multibyte-or-wide-character
* http://cygwin.1069669.n5.nabble.com/Problem-with-dlopen-tp57780p57781.html
* https://stackoverflow.com/questions/1053180/loadlibrary-error-code-127
* http://www.mingw.org/wiki/sampleDLL
* https://docs.microsoft.com/en-us/previous-versions/windows/desktop/mscs/implementing-dllmain

### Cygwin

* https://cygwin.fandom.com/wiki/FAQ
* https://github.com/Alexpux/Cygwin/blob/master/winsup/cygwin/include/dlfcn.h
* https://stackoverflow.com/questions/30128309/cygwin-gcc-error-while-loading-shared-libraries
* https://stackoverflow.com/questions/2710465/reference-a-gnu-c-posix-dll-built-in-gcc-against-cygwin-from-c-net
* https://stackoverflow.com/questions/24413545/dllmain-behaves-oddly-with-g-on-cygwin
* https://cygwin.com/faq.html#faq.programming.huge-executables
* https://cygwin.com/cygwin-ug-net/using.html#mount-table

#### LD_PRELOAD

* https://catonmat.net/simple-ld-preload-tutorial-part-two
* http://cygwin.1069669.n5.nabble.com/Usage-of-LD-PRELOAD-td34989.html
