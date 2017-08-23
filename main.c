
#include "cc.h"
#include "cpp.h"
#include "python.h"
#include "ruby.h"
#undef ASSUME
#include "perl.h"
#include "Haskell_stub.h"

int main(int argc, char** argv) {
  void* null = NULL; // Bypass a compiler warning
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  Py_SetProgramName(program);
  Py_Initialize();
  ruby_init();
  ruby_script(argv[0]);
  PERL_SYS_INIT3(&argc, &argv, null);
  hs_init(&argc, &argv);

  c_print(1);
  cpp_print(2);
  haskellPrint(3);
  python_print(4);
  ruby_print(5);
  perl_print(6);

  hs_exit();
  PERL_SYS_TERM();
  int exit_code = ruby_cleanup(0);
  Py_Finalize();
  PyMem_RawFree(program);
  return exit_code;
}
