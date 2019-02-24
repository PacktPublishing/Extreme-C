// File name: NativeStack.cpp
// Description: C++ implementation of JNI native functions

#include <stdlib.h>

#include "NativeStack.h"
#include "cstack.h"

void defaultDeleter(value_t* value) {
  free_value(value);
}

void extractFromJByteArray(JNIEnv* env,
                           jbyteArray byteArray,
                           value_t* value) {
  jboolean isCopy = false;
  jbyte* buffer = env->GetByteArrayElements(byteArray, &isCopy);
  value->len = env->GetArrayLength(byteArray);
  value->data = (char*)malloc(value->len * sizeof(char));
  for (size_t i = 0; i < value->len; i++) {
    value->data[i] = buffer[i];
  }
  env->ReleaseByteArrayElements(byteArray, buffer, 0);
}

JNIEXPORT jlong JNICALL JNI_FUNC(newStack)(JNIEnv* env, jclass clazz) {
  return (long)cstack_new();
}

JNIEXPORT void JNICALL JNI_FUNC(deleteStack)(JNIEnv* env,
                                            jclass clazz,
                                            jlong stackPtr) {
  cstack_t* cstack = (cstack_t*)stackPtr;
  cstack_delete(cstack);
}

JNIEXPORT void JNICALL JNI_FUNC(ctor)(JNIEnv *env,
                                      jclass clazz,
                                      jlong stackPtr,
                                      jint maxSize) {
  cstack_t* cstack = (cstack_t*)stackPtr;
  cstack_ctor(cstack, maxSize);
}

JNIEXPORT void JNICALL JNI_FUNC(dtor)(JNIEnv* env,
                                      jclass clazz,
                                      jlong stackPtr) {
  cstack_t* cstack = (cstack_t*)stackPtr;
  cstack_dtor(cstack, defaultDeleter);
}

JNIEXPORT jint JNICALL JNI_FUNC(size)(JNIEnv* env,
                                      jclass clazz,
                                      jlong stackPtr) {
  cstack_t* cstack = (cstack_t*)stackPtr;
  return cstack_size(cstack);
}

JNIEXPORT void JNICALL JNI_FUNC(push)(JNIEnv* env,
                                      jclass clazz,
                                      jlong stackPtr,
                                      jbyteArray item) {
  value_t value;
  extractFromJByteArray(env, item, &value);

  cstack_t* cstack = (cstack_t*)stackPtr;
  bool_t pushed = cstack_push(cstack, value);
  if (!pushed) {
    jclass Exception = env->FindClass("java/lang/Exception");
    env->ThrowNew(Exception, "Stack is full!");
  }
}

JNIEXPORT jbyteArray JNICALL JNI_FUNC(pop)(JNIEnv* env,
                                           jclass clazz,
                                           jlong stackPtr) {
  value_t value;
  cstack_t* cstack = (cstack_t*)stackPtr;
  bool_t popped = cstack_pop(cstack, &value);
  if (!popped) {
    jclass Exception = env->FindClass("java/lang/Exception");
    env->ThrowNew(Exception, "Stack is empty!");
  }
  jbyteArray result = env->NewByteArray(value.len);
  env->SetByteArrayRegion(result, 0, value.len, (jbyte*)value.data);
  defaultDeleter(&value);
  return result;
}


JNIEXPORT void JNICALL JNI_FUNC(clear)(JNIEnv* env,
                                       jclass clazz,
                                       jlong stackPtr) {
  cstack_t* cstack = (cstack_t*)stackPtr;
  cstack_clear(cstack, defaultDeleter);
}
