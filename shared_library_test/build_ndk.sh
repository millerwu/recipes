cd crash/jni/
ndk-build
cd ../../
cp crash/libs/armeabi-v7a/libwish_crash.so so/jni/
cp crash/libs/armeabi-v7a/libwish_crash.so elf/jni/

cd so/jni/
ndk-build
cd ../../
cp so/libs/armeabi-v7a/libshared_test.so elf/jni/

cd elf/jni/
ndk-build
cd ../../
