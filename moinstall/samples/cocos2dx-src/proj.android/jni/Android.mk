LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d) 
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos2dx/platform/third_party/android/prebuilt)
$(call import-add-path,$(LOCAL_PATH)/thirdparty/prebuilt)                       # honeycomb

LOCAL_MODULE := game_shared
LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/GameObjects.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/InstructionScene.cpp \
                   ../../Classes/Utility.cpp \
                   ../../Classes/HUDLayer.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/JNIHelpers.cpp \
                   ../../Classes/NativeUtils.cpp \
                   ../../Classes/LevelHelper/LevelHelperLoader.cpp \
                   ../../Classes/LevelHelper/CustomClasses/TemporaryDummyClass.cpp \
                   ../../Classes/LevelHelper/Nodes/LHAnimationNode.cpp \
                   ../../Classes/LevelHelper/Nodes/LHBatch.cpp \
                   ../../Classes/LevelHelper/Nodes/LHBezier.cpp \
                   ../../Classes/LevelHelper/Nodes/LHContactInfo.cpp \
                   ../../Classes/LevelHelper/Nodes/LHContactListener.cpp \
                   ../../Classes/LevelHelper/Nodes/LHContactNode.cpp \
                   ../../Classes/LevelHelper/Nodes/LHCustomSpriteMgr.cpp \
                   ../../Classes/LevelHelper/Nodes/LHCuttingEngineMgr.cpp \
                   ../../Classes/LevelHelper/Nodes/LHFixture.cpp \
                   ../../Classes/LevelHelper/Nodes/LHJoint.cpp \
                   ../../Classes/LevelHelper/Nodes/LHLayer.cpp \
                   ../../Classes/LevelHelper/Nodes/LHNode.cpp \
                   ../../Classes/LevelHelper/Nodes/LHParallaxNode.cpp \
                   ../../Classes/LevelHelper/Nodes/LHPathNode.cpp \
                   ../../Classes/LevelHelper/Nodes/LHSettings.cpp \
                   ../../Classes/LevelHelper/Nodes/LHSprite.cpp \
                   ../../Classes/LevelHelper/Nodes/LHTouchMgr.cpp \
                   ../../Classes/LevelHelper/Nodes/SHDocumentLoader.cpp \
                   ../../Classes/LevelHelper/Utilities/LHArray.cpp \
                   ../../Classes/LevelHelper/Utilities/LHDictionary.cpp \
                   ../../Classes/LevelHelper/Utilities/LHObject.cpp \
                   ../../android/jansson/dump.c \
                   ../../android/jansson/error.c \
                   ../../android/jansson/hashtable.c \
                   ../../android/jansson/load.c \
                   ../../android/jansson/memory.c \
                   ../../android/jansson/pack_unpack.c \
                   ../../android/jansson/strbuffer.c \
                   ../../android/jansson/strconv.c \
                   ../../android/jansson/utf.c \
                   ../../android/jansson/value.c \
                   ../../android/NDKHelper/NDKCallbackNode.cpp \
                   ../../android/NDKHelper/NDKHelper.cpp                    
                   
                   
LOCAL_C_INCLUDES :=$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../Classes/LevelHelper \
$(LOCAL_PATH)/../../libs/cocos2dx/cocoa \
$(LOCAL_PATH)/../../libs \
$(LOCAL_PATH)/../../android/NDKHelper \
$(LOCAL_PATH)/../../android/jansson \
$(LOCAL_PATH)/../../libs/Box2D \
$(LOCAL_PATH)/../../../

LOCAL_C_INCLUDES += $(LOCAL_PATH)/thirdparty/prebuilt/honeycomb/include         # honeycomb


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += honeycomb_static                                # honeycomb

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,extensions) 
$(call import-module,external/Box2D)
$(call import-module,CocosDenshion/android)
$(call import-module,honeycomb)                                                 # honeycomb
