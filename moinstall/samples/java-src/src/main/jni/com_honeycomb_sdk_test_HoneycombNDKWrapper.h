#include <jni.h>

/* Header for class com_honeycomb_sdk_test_HoneycombNDKWrapper */

#ifndef _Included_com_honeycomb_sdk_test_HoneycombNDKWrapper
#define _Included_com_honeycomb_sdk_test_HoneycombNDKWrapper
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Class:     com_honeycomb_sdk_test_HoneycombNDKWrapper
 * Method:    version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_version
  (JNIEnv *, jclass);

/**
 * Class:     com_honeycomb_sdk_test_HoneycombNDKWrapper
 * Method:    prepare
 * Signature: (Landroid/app/Activity;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_prepare
  (JNIEnv *, jclass, jobject, jstring, jstring);

/**
 * Class:     com_honeycomb_sdk_test_HoneycombNDKWrapper
 * Method:    setEnabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_setEnabled
  (JNIEnv *, jclass, jboolean);

/**
 * Class:     com_honeycomb_sdk_test_HoneycombNDKWrapper
 * Method:    isEnabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_isEnabled
  (JNIEnv *, jclass);

/**
 * Class:     com_honeycomb_sdk_test_HoneycombNDKWrapper
 * Method:    showAd
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_showAd
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
