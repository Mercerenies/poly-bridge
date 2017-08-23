
#include <EXTERN.h>
#include <perl.h>
#include "perl.h"

void perl_initialize(int* argc, char*** argv) {
  void* null = NULL;
  PERL_SYS_INIT3(argc, argv, null);
}

void perl_print(int n) {
  char* argv[] = {"", "./perl.pl"};
  PerlInterpreter* my_perl = perl_alloc();
  perl_construct(my_perl);
  perl_parse(my_perl, NULL, 2, argv, NULL);

  dSP;
  ENTER;
  SAVETMPS;
  PUSHMARK(SP);
  EXTEND(SP, 1);
  PUSHs(sv_2mortal(newSViv(n)));
  PUTBACK;

  call_pv("perl_print", G_DISCARD);

  FREETMPS;
  LEAVE;

  perl_destruct(my_perl);
  perl_free(my_perl);
}

void perl_release() {
  PERL_SYS_TERM();
}
