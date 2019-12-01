# CC_OPTS=-Wall -O0 -g -fPIC -fPIE
CC_OPTS=-O0 -g -mgeneral-regs-only -fPIC -fPIE
# CC_TOOL=x86_64-w64-mingw32-gcc ${CC_OPTS} -fPIC -fPIE 
CC_TOOL=gcc ${CC_OPTS}
# CC_TOOL=x86_64-w64-mingw32-clang ${CC_OPTS} 

# The output location of the dll
OUT_DLL=/cygdrive/c/cygwin-test/bin/cygwin1.dll

all: clean generate-resources compile deploy test

generate-resources:
	cygwin-stubify.sh

compile:
	# -Wl,--image-base -Wl,0x180040000
	x86_64-w64-mingw32-gcc ${CC_OPTS} -Wno-builtin-declaration-mismatch -c -o cygwin-stub.o cygwin-stub.c 
	x86_64-w64-mingw32-gcc ${CC_OPTS} -shared -I/usr/include -o fci_cygwin.dll fci_cygwin.c cygwin-stub.o 
	# ${CC_TOOL} -S demo.c
	# ${CC_TOOL} -o demo.exe demo.c
#	${CC_TOOL} -shared -o cygwin_proxy.dll cygwin_proxy.c

clean:
	rm -fr *.{dll,exe,s,stackdump}

deploy:
	cp fci_cygwin.dll ${OUT_DLL}

test:
	# launch-cygwin-test.cmd
	cygstart.exe /cygdrive/c/cygwin-test/bin/mintty.exe -i /Cygwin-Terminal.ico -
	# strace demo
