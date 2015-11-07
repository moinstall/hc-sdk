LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/thirdparty/prebuilt)                               # honeycomb

LOCAL_MODULE                    := honeycombtest_shared

LOCAL_MODULE_FILENAME           := libhoneycombtest

LOCAL_SRC_FILES                 := com_honeycomb_sdk_test_HoneycombNDKWrapper.cpp
                   
LOCAL_C_INCLUDES                := $(LOCAL_PATH)/thirdparty/prebuilt/honeycomb/include  # honeycomb

LOCAL_CFLAGS                    := -std=c++11

LOCAL_LDLIBS	                := -llog -lz

LOCAL_WHOLE_STATIC_LIBRARIES    := honeycomb_static                                     # honeycomb

include $(BUILD_SHARED_LIBRARY)

$(call import-module,honeycomb)                                                         # honeycomb
