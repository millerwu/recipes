LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := shared_test
LOCAL_SRC_FILES := shared_test.cpp
LOCAL_LDFLAGS += -Og
LOCAL_LDLIBS += -L ./ -lwish_crash
include $(BUILD_SHARED_LIBRARY)