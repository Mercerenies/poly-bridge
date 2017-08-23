
#include "cpp.h"
#include <iostream>

extern "C" {

  void cpp_print(int n) {
    std::cout << n << ". Printing from C++" << std::endl;
  }

}
