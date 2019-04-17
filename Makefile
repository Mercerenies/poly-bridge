
OBJECTS=main.o cc.o cpp.o Haskell.o haskell.o python.o ruby.o perl.o lua.o tcl.o

PERL_CORE=$(shell perl -MConfig -e 'print $$Config{archlib}')

.PHONY:	all clean

all:	poly

clean:
	rm *.o *.hi Haskell_stub.h poly

poly:	$(OBJECTS) librust.a
	ghc -L$(PERL_CORE)/CORE -lstdc++ -lperl -ltcl8.6 $(shell pkg-config --libs python3 ruby lua5.1) -no-hs-main $(OBJECTS) librust.a -o poly

main.o:	main.c cc.h cpp.h Haskell_stub.h python.h ruby.h haskell.h rust.h tcl.h
	gcc -c main.c -o main.o

cc.o: cc.c cc.h
	gcc -c cc.c -o cc.o

cpp.o: cpp.cpp cpp.h
	g++ -c cpp.cpp -o cpp.o

Haskell_stub.h:	Haskell.o

Haskell.o:	Haskell.hs
	ghc Haskell.hs

haskell.o:	haskell.c haskell.h
	gcc -I/usr/lib/ghc/include -c haskell.c -o haskell.o

python.o:	python.c python.h
	gcc $(shell pkg-config --cflags python3) -c python.c -o python.o

ruby.o:	ruby.c ruby.h
	gcc $(shell pkg-config --cflags ruby) -c ruby.c -o ruby.o

perl.o:	perl.c perl.h
	gcc -I$(PERL_CORE)/CORE -c perl.c -o perl.o

lua.o:	lua.c lua.h
	gcc $(shell pkg-config --cflags lua5.1) -c lua.c -o lua.o

librust.a:	rust.rs rust.h
	rustc rust.rs

tcl.o:	tcl.c tcl.h
	gcc -I/usr/include/tcl8.6 -c tcl.c -o tcl.o
