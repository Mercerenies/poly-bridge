
#include "cc.h"
#include "cpp.h"
#include "python.h"
#include "ruby.h"
#include "perl.h"
#include "haskell.h"
#include "lua.h"

int main(int argc, char** argv) {
  python_initialize(&argc, &argv);
  ruby_initialize(&argc, &argv);
  perl_initialize(&argc, &argv);
  haskell_initialize(&argc, &argv);
  lua_initialize(&argc, &argv);

  c_print(1);
  cpp_print(2);
  haskell_print(3);
  python_print(4);
  ruby_print(5);
  perl_print(6);
  lua_print(7);

  lua_release();
  haskell_release();
  perl_release();
  ruby_release();
  python_release();
  return 0;
}
