#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

// #define TEST_DLOPEN

#ifdef TEST_DLOPEN
typedef void (*fun_test)(void);
#else
void shared_test();
#endif


int main()
{

#ifdef TEST_DLOPEN
    fun_test shared_test;
    
    void* handle = dlopen("/system/lib/libshared_test.so", RTLD_LAZY);
    if (!handle) {
      printf("libshared_test.so open \n");
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
    }

    shared_test = (fun_test)dlsym(handle, "shared_test");
#endif

    shared_test();

#ifdef TEST_DLOPEN
    if (dlclose(handle) < 0) {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
    }
#endif
}