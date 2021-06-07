
LOCAL_PATH := $(call my-dir)

LOCAL_MODULE := ion_test
LOCAL_MODULE_FILENAME := ion_test
LOCAL_CPP_EXTENSION := .cxx .cpp
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_SRC_FILES := ion_test.cpp
include $(BUILD_EXECUTABLE)
