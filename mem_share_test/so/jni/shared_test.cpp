#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void wishCrash();

void shared_test()
{
  char str[] = "Hello Shared Lib";
  printf("%s \n", str);
  wishCrash();
  return;
}