# Honeycomb SDK Android Integration Tutorial

## Intro
Honeycomb SDK help you to easy integration if Honeycomb ad network into your application.

Honeycomb SDK for Android support currently support
 * cocos2dx / NDK apps
 * native java apps with both `ant` and `gradle` build systems 

## Package content
1. Android native module for major CPU architectures (armv5, armv7, x86)
2. library project for Ant-based project 
3. aar library for gradle-based projects 

Tree of content looks like this
```
├── ant
│   ├── res
│   ├── src
│   ├── jni
│   ├── libs
│   └── project.properties
├── gradle
│   └── honeycomb-sdk-release.aar
├── ndk-module
│   └── cocos2dx
│       ├── Android.mk
│       ├── include
│       │   └── honeycomb.h
│       └── libs
│           ├── armeabi
│           │   └── libhoneycomb.a
│           ├── armeabi-v7a
│           │   └── libhoneycomb.a
│           └── x86
│               └── libhoneycomb.a
└── samples
    ├── apk
    │   └── cocos2dx-sample-2-debug.apk
    └── cocos2dx-src
        ├── Classes
        ├── Resources
        └── proj.android
```

## Integration

As you may noticed above sdk have different set of files for:

 * gradle based projects
 * ant based projects

Until recent time all cocos2dx apps used `ant` as build system, but now `cocos2dx` support `gradle` also, so here we have possible variations here:

 * cocos2d-x gradle project
 * cocos2d-x ant project
 * java gradle project
 * java ant project

Let’s review all this variants below

### cocos2d-x gradle project

Steps to do:
1. add `honeycomb-sdk-release.aar` file to libs directory and update dependencies section in your `build.gradle`, like this:

    ```
    repositories {
        flatDir {
            dirs 'libs'
        }
    }
    
    dependencies {
        compile(name:'honeycomb-sdk-release', ext:'aar')
    }
    ```
2. Update `Android.mk` file

    ```
    LOCAL_PATH := $(call my-dir)
    
    include $(CLEAR_VARS)
    
    $(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
    $(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
    $(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
    $(call import-add-path,$(LOCAL_PATH)/thirdparty/prebuilt)                      # honeycomb                    
    
    LOCAL_MODULE := cocos2dcpp_shared
    
    LOCAL_MODULE_FILENAME := libcocos2dcpp
    
    LOCAL_SRC_FILES := hellocpp/main.cpp \
                       ../../Classes/AppDelegate.cpp \
                       ../../Classes/HelloWorldScene.cpp
    
    LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
    LOCAL_C_INCLUDES += $(LOCAL_PATH)/thirdparty/prebuilt/honeycomb/include       # honeycomb
    
    # _COCOS_HEADER_ANDROID_BEGIN
    # _COCOS_HEADER_ANDROID_END
    
    LOCAL_CFLAGS += -DCOCOS2D_DEBUG=1
    
    LOCAL_STATIC_LIBRARIES := cocos2dx_static
    LOCAL_STATIC_LIBRARIES += honeycomb_static                                   # honeycomb
    
    # _COCOS_LIB_ANDROID_BEGIN
    # _COCOS_LIB_ANDROID_END
    
    include $(BUILD_SHARED_LIBRARY)
    
    $(call import-module,.)
    $(call import-module,honeycomb)                                              # honeycomb
    
    # _COCOS_LIB_IMPORT_ANDROID_BEGIN
    # _COCOS_LIB_IMPORT_ANDROID_END
    ```
3. modify `cocos_android_app_init` function in `main.cpp` file

    ```
    #include "AppDelegate.h"
    ...
    #include <honeycomb.h>                                                         // honeycomb
    ...
    void cocos_android_app_init (JNIEnv* env, jobject thiz) {
        LOGD("cocos_android_app_init");
    
        Honeycomb_Init(env, “your appId”);                                         // honeycomb
    
        LOGD("mosdk version %s", VersionInfo());

        AppDelegate *pAppDelegate = new AppDelegate();
    }
    ```

It’s all, now you can use `Honeycomb_ShowAd` where you needed.

### cocos2d-x ant project
1. place ant project to you project tree, and prepare it by run in terminal

    ```
    android update lib-project $path/to/honeycomb-eclipse
    ```
2. add `honeycomb-eclipse` ant project to `project.properties` config
3. modify `Android.mk` see [cocos2d-x gradle project#2](#cocos2d-x-gradle-project)
4. modify `cocos_android_app_init` function in `main.cpp` file, see [cocos2d-x gradle project#3](#cocos2d-x-gradle-project)

It’s all, now you can use `Honeycomb_ShowAd` where you needed.

### java gradle project
Do [cocos2d-x gradle project#1](#cocos2d-x-gradle-project)

After this you will able use `Honeycomb.*` methods

### java ant project
Do [cocos2d-x ant project#1](#ccocos2d-x-ant-project)

After this you will able use `Honeycomb.*` methods

