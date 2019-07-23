#include <stdio.h>

extern int add(int a, int b);
extern int minus(int a, int b);
extern int bar(int a, int b);
extern int foo(int a, int b);

int main() {
    int add_res = add(1, 2);
    int minus_res = minus(2, 1);
    int bar_res = bar(1, 2);
    int foo_res = foo(1, 2);
    printf("ndk sample \n");
    return 0;
}