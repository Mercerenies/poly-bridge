
#include <stdlib.h>
#include <tcl.h>

Tcl_Interp* tcl_interp;

void tcl_initialize(int* argc, char*** argv) {
  tcl_interp = Tcl_CreateInterp();
  Tcl_Preserve(tcl_interp);
}

void tcl_print(int n) {

  char fnname[] = "tclPrint";

  int objc = 2;
  Tcl_Obj** objv = malloc(sizeof(Tcl_Obj*) * 2);
  objv[0] = Tcl_NewStringObj(fnname, sizeof(fnname));
  objv[1] = Tcl_NewIntObj(n);

  Tcl_IncrRefCount(objv[0]);
  Tcl_IncrRefCount(objv[1]);

  Tcl_EvalFile(tcl_interp, "tcl.tcl");
  Tcl_EvalObjv(tcl_interp, objc, objv, 0);

  Tcl_DecrRefCount(objv[0]);
  Tcl_DecrRefCount(objv[1]);

  free(objv);

}

void tcl_release() {
  Tcl_Release(tcl_interp);
  Tcl_DeleteInterp(tcl_interp);
}
