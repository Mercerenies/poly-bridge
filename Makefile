
OBJECTS=main.o cc.o cpp.o Haskell.o haskell.o python.o ruby.o perl.o lua.o tcl.o java.o

PERL_CORE=$(shell perl -MConfig -e 'print $$Config{archlib}')
LUA_CFLAGS=$(shell pkg-config --silence-errors --cflags lua5.1 || pkg-config --cflags lua5.2)
LUA_LIBS=$(shell pkg-config --silence-errors --libs lua5.1 || pkg-config --libs lua5.2)
JAVA_HOME=$(shell locate jni.h | sed 's/include.jni.h//')

.PHONY:	all clean run

all:	poly

clean:
	rm *.o *.hi Haskell_stub.h *.a *.class poly

run:
	@LD_LIBRARY_PATH=$(JAVA_HOME)/lib/server ./poly

poly:	$(OBJECTS) Java.class librust.a
	ghc -L$(PERL_CORE)/CORE -L$(JAVA_HOME)/lib/server -lstdc++ -lperl -ltcl8.6 -ljvm $(shell pkg-config --libs python3 ruby) $(LUA_LIBS) -no-hs-main $(OBJECTS) librust.a -o poly

main.o:	main.c cc.h cpp.h Haskell_stub.h python.h ruby.h haskell.h rust.h tcl.h java.h
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
	gcc $(LUA_CFLAGS) -c lua.c -o lua.o

librust.a:	rust.rs rust.h
	rustc rust.rs

tcl.o:	tcl.c tcl.h
	gcc -I/usr/include/tcl8.6 -c tcl.c -o tcl.o

java.o:	java.c java.h
	gcc -I$(JAVA_HOME)/include -I$(shell locate jni_md.h | sed 's/jni_md.h//') -c java.c -o java.o

Java.class:	Java.java
	javac Java.java
