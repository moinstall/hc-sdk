/**
 * honeycomb.h
 *
 *  Created on: Jun 26, 2015
 *      Author: camobap
 */

#pragma once

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callbacks table any method can be NULL
 */
typedef struct {
    void (*onAdDownloading) (void);
    void (*onAdDownloaded)  (void);
    void (*onAdShow)        (void);
    void (*onAdClick)       (void);
    void (*onAdClose)       (void);
    void (*onError)         (const char *reason);
} HCCallbackTable;

#ifdef __ANDROID__
void Honeycomb_Init(JNIEnv *env, const char *companyId, const char *appId);
#elif __APPLE__
void Honeycomb_Init(const char *companyId, const char *appId);
#endif

void Honeycomb_Listener(const HCCallbackTable* listener);

void Honeycomb_Cache();

void Honeycomb_ShowAd();

/**
 * @return version string, caller responsible for free response
 */
const char* Honeycomb_Version(void);

bool Honeycomb_Enabled(void);

void Honeycomb_Switch(bool enabled);

#ifdef __cplusplus
}
#endif


