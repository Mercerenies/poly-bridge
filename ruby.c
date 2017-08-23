
#include "ruby.h"

void ruby_print(int n) {
  VALUE arg = LONG2FIX(n);
  VALUE obj = rb_require("./ruby.rb");
  rb_funcall(obj, rb_intern("ruby_print"), 1, arg);
}
