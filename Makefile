
OBJECTS=main.o cc.o cpp.o Haskell.o haskell.o python.o ruby.o perl.o

PERL_CORE=$(shell perl -MConfig -e 'print $$Config{archlib}')

.PHONY:	all clean

all:	poly

clean:
	rm *.o *.hi Haskell_stub.h poly

poly:	$(OBJECTS)
	ghc -L$(PERL_CORE)/CORE -lstdc++ -lperl $(shell pkg-config --libs python3 ruby) -no-hs-main $(OBJECTS) -o poly

main.o:	main.c cc.h cpp.h Haskell_stub.h python.h ruby.h haskell.h
	gcc -I$(PERL_CORE)/CORE -I/usr/lib/ghc/include $(shell pkg-config --cflags python3 ruby) -c main.c -o main.o

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
