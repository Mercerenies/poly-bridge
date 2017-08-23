
#include "haskell.h"
#include "Haskell_stub.h"

void haskell_initialize(int* argc, char*** argv) {
  hs_init(argc, argv);
}

void haskell_print(int n) {
  haskellPrint(n);
}

void haskell_release() {
  hs_exit();
}
