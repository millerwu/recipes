rm -rf unix_output/*
g++ crash/jni/crash.cpp -g -shared -fpic -o unix_output/libwish_crash.so
g++ so/jni/shared_test.cpp -g -shared -fpic -Lunix_output/ -lwish_crash -o unix_output/libshared_test.so
g++ elf/jni/test_main.cpp -g -Lunix_output/ -lwish_crash -lshared_test -o unix_output/test