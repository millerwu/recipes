adb root
adb remount

adb push ./crash/libs/armeabi-v7a/libwish_crash.so /system/lib
adb push ./so/libs/armeabi-v7a/libshared_test.so /system/lib
adb push ./elf/libs/armeabi-v7a/test /system/bin

adb shell /system/bin/test