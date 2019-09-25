// File name: NativeStack.h
// Description: Modified JNI generated header file

#include <jni.h>

#ifndef _Included_com_packt_extreme_c_ch21_ex1_NativeStack
#define _Included_com_packt_extreme_c_ch21_ex1_NativeStack

#define JNI_FUNC(n) Java_com_packt_extreme_1c_ch21_ex1_NativeStack_##n

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL JNI_FUNC(newStack)(JNIEnv* , jclass);
JNIEXPORT void JNICALL JNI_FUNC(deleteStack)(JNIEnv* , jclass, jlong);

JNIEXPORT void JNICALL JNI_FUNC(ctor)(JNIEnv* , jclass, jlong, jint);
JNIEXPORT void JNICALL JNI_FUNC(dtor)(JNIEnv* , jclass, jlong);

JNIEXPORT jint JNICALL JNI_FUNC(size)(JNIEnv* , jclass, jlong);

JNIEXPORT void JNICALL JNI_FUNC(push)(JNIEnv* , jclass, jlong, jbyteArray);
JNIEXPORT jbyteArray JNICALL JNI_FUNC(pop)(JNIEnv* , jclass, jlong);

JNIEXPORT void JNICALL JNI_FUNC(clear)(JNIEnv* , jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
