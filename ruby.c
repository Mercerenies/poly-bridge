
#include <ruby.h>
#include "ruby.h"

void ruby_initialize(int* argc, char*** argv) {
  ruby_init();
  ruby_script(argv[0][0]);
}

void ruby_print(int n) {
  VALUE arg = LONG2FIX(n);
  VALUE obj = rb_require("./ruby.rb");
  rb_funcall(obj, rb_intern("ruby_print"), 1, arg);
}

void ruby_release() {
  ruby_cleanup(0);
}
