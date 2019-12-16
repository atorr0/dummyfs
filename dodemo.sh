#!/bin/bash

# nm -g /bin/cygwin1.dll | cut -f2- -d' ' | grep '^T ' | cut -c3-
# cat $0.names.txt | sed -En -e 's:$:\0 = GetProcAddress(hL,"\0");:' | head
# cat proxy_cygwin.sh.names.txt | sed -En -e 's:$:\0 = GetProcAddress(hL,"\0");:' | head
# cat proxy_cygwin.sh.names.txt | sed -E -e 's:$:a:' | head
# cat proxy_cygwin.sh.names.txt | sed -E -e 's:.*:\0 = :' | head

standard () {
    export LD_PRELOAD=/cygdrive/c/Git/dummyfs/fci_cygwin.dll

    echo "LD_PRELOAD:$LD_PRELOAD"
    cat -n demo.c

    echo "LD_PRELOAD:$LD_PRELOAD"
    head -3 demo.c

    bash -c 'echo LD_PRELOAD [$LD_PRELOAD]; cat -n demo.c'
    echo "Exited with $?"
}

strace () {
    export LD_PRELOAD=/Git/dummyfs/fci_cygwin.dll
    strace demo
}

debug () {
    cat>.gdb.txt<<-EOF
    set environment LD_PRELOAD ./fci_cygwin.dll
    file demo.exe
    set disassembly-flavor intel
    break main
    break 21
    start
    info sharedlibrary
EOF

    gdb --init-command=gdb.txt
}

# debug w/o de fci_cygwin.dll
simple-debug () {
    cat>.gdb.txt<<-EOF
    file demo.exe
    set disassembly-flavor intel
    break main
    break 21
    start
    info sharedlibrary
EOF

    gdb --init-command=gdb.txt
}

cygwin-test () {

    launch-cygwin-test.cmd
}

do-mount () {
    local _T=$(mktemp -d)
    ls -ld $_T
    export LD_PRELOAD=/Git/dummyfs/fci_cygwin.dll
    mount  fci:dummyfs:-readonly,-test=whatever-value $_T
    ls -ld $_T
}

if [ $# -eq 0 ]; then
    standard
else
    $*
fi
