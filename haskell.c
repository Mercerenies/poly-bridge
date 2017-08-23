
#include "haskell.h"
#include "Haskell_stub.h"

void haskell_init(int* argc, char*** argv) {
  hs_init(argc, argv);
}

void haskell_print(int n) {
  haskellPrint(n);
}

void haskell_free() {
  hs_exit();
}
