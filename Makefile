# CC_OPTS=-Wall -O0 -g -fPIC -fPIE
CC_OPTS=-O0 -g -mgeneral-regs-only
# CC_TOOL=x86_64-w64-mingw32-gcc ${CC_OPTS} -fPIC -fPIE 
CC_TOOL=gcc ${CC_OPTS} -fPIC -fPIE
# CC_TOOL=x86_64-w64-mingw32-clang ${CC_OPTS} 

all: clean generate-resources compile test

generate-resources:
#	proxy_cygwin.sh

compile:
	${CC_TOOL} -shared -o fci_cygwin.dll fci_cygwin.c -Wl,--image-base -Wl,0x10000000
	${CC_TOOL} -S demo.c
	${CC_TOOL} -o demo.exe demo.c
#	${CC_TOOL} -shared -o cygwin_proxy.dll cygwin_proxy.c

clean:
	rm -fr *.{dll,exe,s,stackdump}

test:
	./dodemo.sh
	# strace demo
