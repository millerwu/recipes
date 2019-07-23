# NDK 编译系统包里的变量名
# 1. 以 LOCAL_ 开头的名称，例如 LOCAL_MODULE
# 2. PRIVATE_, NDK_ 和 APP_ 开头的名称。编译系统在内部使用这些变量名
# 3. 小写名称， 例如 my-dir
# 自定义变量建议在前面加上 MY_

# 编译系统会根据 API_ABI 变量所指定的每个 ABI 解析Android.mk 一次
# TARGET_ARCH 编译系统解析 Android.mk 文件时面向的 CPU 系列，可以是 arm, arm64, x86, x86_64

# TARGET_PLATFORM 编译系统解析 Android.mk 时面向的 Android API 级别编号，例如 Android5.1 对应的是 android-22

# TARGET_ARCH_ABI 编译系统解析 Android.mk 时面向的 ABI。不同的 CPU 架构对应的 ABI 设置如下：
# ARMv7 ==> armeabi-v7a
# ARMv8 AArch64 ==> arm64-v8a
# i686 ==> x86
# x86-64 ==> x86_64
# e.g. ifeq ($(TARGET_ARCH_ABI), arm64-v8a)

# TARGET_ABI 目标 Android API 和 ABI 的连接， 适合要针对实际设备测试特定目标系统镜像的情况。
# e.g. ifeq ($(TARGET_ABI), android-22-arm64-v8a)


# all-subdir-makefiles 返回当前 my-dir 路径下所有子目录的 Android.mk 文件列表。利用这个函数，可以为编译系统提供深度嵌套的源目录层次结构
# this-makefile 返回当前 makefile 路径
# parent-makefile 返回包含树中父 makefile 的路径
# grand-parent-makefile 返回包含树中祖父 makefile 的路径
# import-module 用于按照模块名称查找和包含模块的 Android.mk 文件
# e.g. $(call import-module,<name>)
# my-dir 返回包含 Android.mk的目录


# LOCAL_PATH 用于指定当前文件的路径
LOCAL_PATH := $(call my-dir)

# CLEAR_VARS 清除几乎所以的 LOCAL_XXX 变量，LOCAL_PATH 除外
include $(CLEAR_VARS)
LOCAL_MODULE := foo
LOCAL_SRC_FILES := ${LOCAL_PATH}/lib/libfoo.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := bar
LOCAL_SRC_FILES := ${LOCAL_PATH}/lib/libbar.so
# LOCAL_EXPORT_C_INCLUDES 定义会确保编译系统导出指定预编译库的 include 路径，针对依赖于它的模块将改路径附加到 LOCAL_C_INCLUDES 的值
LOCAL_EXPORT_C_INCLUDES := 
# LOCAL_EXPORT_CFLAGS 用于记录一组 c/c++编译机标记，这些标记将通过 LOCAL_STATIC_LIBRARIES 或 LOCAL_SHARED_LIBRARIES 变量使用此模块的任何其他模块的 LOCAL_CFLAGS 定义中
# 执行局部编译时，不使用导出的标记
# PREBUILT_SHARED_LIBRARY 用于指定预编译共享库的编译脚本，这里的 LOCAL_SRC_FILES 不能是源文件，必须是指向预编译共享库的一个路径
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := minus
LOCAL_SRC_FILES := minus.cpp
# 用于编译静态库，需要注意的是，系统不会将静态库赋值到项目/软件包中，但是可以使用静态库编译共享库
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := add
LOCAL_SRC_FILES := add.cpp
# BUILD_SHARED_LIBRARY 用于指向编译脚本用于收集 LOCAL_XXX变量中提供的模块的所有相关信息，以确定如何根据列出的源文件编译目标共享库
# 系统会生成扩展名为.so的库文件
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

# LOCAL_STATIC_LIBRARIES 用于存储当前模块依赖的静态库模块列表
# LOCAL_SHARED_LIBRARIES 用于存储当前模块运行时依赖的共享库的列表，是链接时的必要信息，编译时会将相应的信息嵌入到生成的文件中
LOCAL_SHARED_LIBRARIES := add \
                         minus \
                         bar \
                         foo

# LOCAL_WHOLE_STATIC_LIBRARIES 表示链接器应将相应的库模块视为完整归档。完整归档，参见 GUI ID 文档的 --whole-archive 标记部分
# LOCAL_WHOLE_STATIC_LIBRARIES 在多个静态库之间存在循环依赖时很有用。使用它编译共享库时，它将强制编译系统将静态库中所有对象文件添加到最终二进制文件中。但是生成可执行文件时不会发生这种情况

# LOCAL_LDLIBS 用于列出便于共享库或者可执行文件时使用的额外链接器标记。利用这个变量，可以使用-l 前缀传递特定系统的名称，也可以使用-L 来指定共享库链接路径
# e.g. LOCAL_LDLIBS := -L$(LOCAL_PATH)/lib -lz

# LOCAL_LDFLAGS 用于列出编译系统在编译共享库或者可执行文件时使用的其他链接库标记

# LOCAL_CFLAGS 用于编译 c/c++源文件时要传递的编译器选项，可以指定额外的宏定义和编译选项
# LOCAL_CFLAGS 也可以用于指定额外的 include 路径
# LOCAL_CFLAGS += -I<path>
# LOCAL_CPPFLAGS 仅对C++生效
# LOCAL_C_INCLUDES 指出相对于 NDK root 目录的路径列表，在编译源文件时添加到 include 搜索路径

# LOCAL_MODULE 用于储存模块名称，名称必须唯一，且不得包含任何空格。必须在包含任何脚本（CLEAR_VARS脚本除外）之前定义此变量，无需添加 lib 前缀或者.so 和.a 文件扩展名，系统会自动进行修改

LOCAL_MODULE := sample
# LOCAL_MODULE_FILENAME 强制系统生成文件名
LOCAL_MODULE_FILENAME := sample
# LOCAL_CPP_EXTENSION 指明 .cpp 外的扩展名
LOCAL_CPP_EXTENSION := .cxx .cpp
# LOCAL_CPP_FEATURES 指明代码依赖于指定的C++功能
LOCAL_CPP_FEATURES := rtti exceptions
# LOCAL_SRC_FILES 包含编译系统生成模块时所用的所有源文件列表
LOCAL_SRC_FILES := sample.cpp
include $(BUILD_EXECUTABLE)
