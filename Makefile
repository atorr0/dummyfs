# CC_OPTS=-Wall -O0 -g -fPIC -fPIE
CC_OPTS=-O0 -g -fPIC -fPIE -mgeneral-regs-only
CC_TOOL=x86_64-w64-mingw32-gcc ${CC_OPTS} 
# CC_TOOL=gcc ${CC_OPTS} 

all: clean generate-resources compile test

generate-resources:
#	proxy_cygwin.sh

compile:
#	${CC_TOOL} -shared -o hook.dll hook.c
	${CC_TOOL} -S demo.c
	${CC_TOOL} -o demo.exe demo.c
#	${CC_TOOL} -shared -o cygwin_proxy.dll cygwin_proxy.c

clean:
	rm -fr *.{dll,exe,txt,s}

test:
#	dodemo.sh
	demo
