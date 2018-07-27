#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void wishCrash()
{
  char str[] = "Hello wishCrash";
  printf("%s enter \n", str);
  void* p = NULL;
  memset(p, 0xff, 100);
}
