#!/bin/bash
#
# Fills the cygwin-stub.c template from cygwin1.dll symbols.
#

# nm -g /bin/cygwin1.dll | cut -f2- -d' ' | grep '^T ' | cut -c3-
# cat $0.names.txt | sed -En -e 's:$:\0 = GetProcAddress(hL,"\0");:' | head
# cat proxy_cygwin.sh.names.txt | sed -En -e 's:$:\0 = GetProcAddress(hL,"\0");:' | head
# cat proxy_cygwin.sh.names.txt | sed -E -e 's:$:a:' | head
# cat proxy_cygwin.sh.names.txt | sed -E -e 's:.*:\0 = :' | head

TMP1=$(mktemp)
TMP2=$(mktemp)

list-exported-syms () {
    nm -g /bin/cygwin1.dll | cut -f2- -d' ' | grep '^T ' | cut -c3-
}

fill-pointers () {
    # GETPROCADDRESS-POINTERS

    sed -E -e 's:^:HMODULE _pa:' -e 's:$:;:' $TMP1 >$TMP2
    sed -i -E -e "/GETPROCADDRESS-POINTERS/r$TMP2" cygwin-stub.c
}

fill-calls () {
    # GETPROCADDRESS-CALLS

    sed -E -e 's:.*:\0 ();\nasm (".global \0                             \\n\\t"\n"\0\:                                    \\n\\t"\n"       jmp *_pa\0                     \\n\\t");\n:' -e 's:^:__stdcall void :' $TMP1 >$TMP2
    sed -i -E -e "/GETPROCADDRESS-CALLS/r$TMP2" cygwin-stub.c
}

fill-init-pointers () {
    # GETPROCADDRESS-INIT-POINTERS

    sed -E -e 's:.*:    _pa\0 = GetProcAddress(hdll,"\0");:' $TMP1 >$TMP2
    sed -i -E -e "/GETPROCADDRESS-INIT-POINTERS/r$TMP2" cygwin-stub.c
}

#
# main
#

main () {

    # 1. Syms with @ can't be exported as-is
    # 2. Builtin symbols can't be exported
    # 3. Collisions with #include <windows.h> from fci_cygwin.c

    list-exported-syms | fgrep -v '@' \
        | egrep -v 'GetProcAddress|_[Ee]xit|exit|bcopy|bzero|free|sincos[fl]?' \
        | egrep -v 'DeleteCriticalSection|EnterCriticalSection|FreeLibrary|GetCurrentProcess|GetCurrentProcessId|GetCurrentThreadId|GetLastError|GetStdHandle|GetSystemTimeAsFileTime|InitializeCriticalSection|LeaveCriticalSection|QueryPerformanceCounter|Sleep|TerminateProcess|TlsGetValue' \
        > $TMP1


    cat>cygwin-stub.c<<-EOF
    /**
    * @generated Autogenerated stub of exported functions of cygwin1.dll.
    * @see cygwin-stubify.sh
    */
    // #include <windows.c>

    typedef void * HMODULE;

    void * GetProcAddress(HMODULE, const char*);

    // GETPROCADDRESS-POINTERS

    // GETPROCADDRESS-CALLS

    int _initPAPointers(HMODULE hdll) {

        // GETPROCADDRESS-INIT-POINTERS

        return 1;
    }
EOF

    fill-pointers
    fill-calls
    fill-init-pointers
}


main