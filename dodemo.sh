#!/bin/bash

# nm -g /bin/cygwin1.dll | cut -f2- -d' ' | grep '^T ' | cut -c3-
# cat $0.names.txt | sed -En -e 's:$:\0 = GetProcAddress(hL,"\0");:' | head
# cat proxy_cygwin.sh.names.txt | sed -En -e 's:$:\0 = GetProcAddress(hL,"\0");:' | head
# cat proxy_cygwin.sh.names.txt | sed -E -e 's:$:a:' | head
# cat proxy_cygwin.sh.names.txt | sed -E -e 's:.*:\0 = :' | head

standard_run () {
    export LD_PRELOAD=fci_cygwin.dll
    ./demo
}

trace_run () {
    export LD_PRELOAD=fci_cygwin.dll
    strace demo
}

debug_run () {
    gdb --init-command=gdb.txt
}

debug_run