LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := test
LOCAL_SRC_FILES := test_main.cpp
LOCAL_CPPFLAGS += -Og
LOCAL_LDLIBS += -L ./ -lshared_test
include $(BUILD_EXECUTABLE)