
#include <stdlib.h>
#include <jni.h>
#include "assert.h"

JavaVM* jvm;
JNIEnv* env;

void java_initialize(int* argc, char*** argv) {
  JavaVMInitArgs args;
  JavaVMOption opts;

  opts.optionString = "-Djava.class.path=.";
  args.version = JNI_VERSION_1_6;
  args.nOptions = 1;
  args.options = &opts;
  args.ignoreUnrecognized = 0;

  JNI_CreateJavaVM(&jvm, (void**)&env, &args);

}

void java_print(int n) {
  jclass cls = (*env)->FindClass(env, "Java");
  assert(cls != NULL);

  jmethodID mthd = (*env)->GetStaticMethodID(env, cls, "javaPrint", "(I)V");
  assert(mthd != NULL);

  jvalue args[] = { n };

  (*env)->CallStaticVoidMethodA(env, cls, mthd, args);

}

void java_release() {
  (*jvm)->DestroyJavaVM(jvm);
}
