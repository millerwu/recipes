LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := wish_crash
LOCAL_SRC_FILES := crash.cpp
LOCAL_LDFLAGS += -Og
include $(BUILD_SHARED_LIBRARY)