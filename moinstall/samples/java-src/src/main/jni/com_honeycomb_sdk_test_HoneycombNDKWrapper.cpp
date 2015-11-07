#include "com_honeycomb_sdk_test_HoneycombNDKWrapper.h"

#include "honeycomb.h"

JNIEXPORT jstring JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_version
  (JNIEnv *env, jclass) {

  const char* versionCStr = Honeycomb_Version();

  return env->NewStringUTF(versionCStr);
}

JNIEXPORT void JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_prepare
  (JNIEnv *env, jclass, jobject, jstring companyId, jstring appId) {
    const char* companyIdCStr = env->GetStringUTFChars(companyId, nullptr);
    const char* appIdCStr = env->GetStringUTFChars(appId, nullptr);

    Honeycomb_Init(env, companyIdCStr, appIdCStr);

    env->ReleaseStringUTFChars(companyId, companyIdCStr);
    env->ReleaseStringUTFChars(appId, appIdCStr);
}

JNIEXPORT void JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_setEnabled
  (JNIEnv *, jclass, jboolean enabled) {
  Honeycomb_Switch(enabled);
}

JNIEXPORT jboolean JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_isEnabled
  (JNIEnv *, jclass) {
  return Honeycomb_Enabled();
}

JNIEXPORT void JNICALL Java_com_honeycomb_sdk_test_HoneycombNDKWrapper_showAd
  (JNIEnv *, jclass) {
  Honeycomb_ShowAd();
}