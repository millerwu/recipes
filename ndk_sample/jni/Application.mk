# APP_ABI 设置特定的 API 生成代码，不同指令集 APP_ABI 设置举例
# APP_ABI := armeabi-v7a // 32 位 ARMv7
# APP_ABI := arm64-v8a  // 64 位 ARMv8 （AArch64）
# APP_ABI := x86 
# APP_ABI := x86-64
# APP_ABI := all
# 也可指定多个选项，用空格分隔
# APP_ABI := x86 arm64-v8a
APP_ABI := armeabi-v7a 
# APP_PLATFORM 指定的 Android 平台，并对应于应用的 minSdkVersion
APP_PLATFORM := android-21
MY_APP_DIR := $(call my-dir)
# 设置 Android.mk 的路径
APP_BUILD_SCRIPT := $(MY_APP_DIR)/Android.mk

# APP_CFLAGS 为项目中的 C/C++编译传递的标记
# APP_CPPFLAGS 为项目中的 C++编译传递的标记
# APP_CXXFLAGS 与APP_CPPFLAGS相同，但在编译命令中将出现在APP_CPPFLAGS 之后
# APP_STL 用于此应用的 C++标准库。默认情况使用system STL，其他选项包括 c++_shared、c++_static 和 none
# system STL 指的是/system/lib/libstdc++.so，这个库和 GNU 的全功能 libstlc++不同，它只包含 new 和 delete 功能。 system STL 在 NDK r18中移除了
APP_STL := c++_shared

# APP_STRIP_MODE 用于给应用传递 strip 参数，默认参数为 --strip-unneeded
# APP_THIN_ARCHIVE 用于为项目中的静态库使用瘦归档，将此变量设置为 True