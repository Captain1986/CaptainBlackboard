//main2.cpp
#include <stdio.h>
#include <stdlib.h>
#include "3rd_lib.h"

int main(int argc, char* argv[])
{
  printf("TAG: print to stdout.\n");

  _3rd_lib_func();

  FILE *fp = NULL;
  fp = freopen("/dev/null", "r", stdout);
  if(fp!=NULL){
	fprintf(stderr, "TAG: print to stderr\n");
	printf("TAG: print to stdout\n");
  }

  _3rd_lib_func();

  return 0;
}
