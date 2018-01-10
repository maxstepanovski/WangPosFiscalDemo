#include <jni.h>
#include <string>
#include "pn548_i2c_testapp.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_mamba_wangposfiscaldemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    main();
    return env->NewStringUTF(hello.c_str());
}
