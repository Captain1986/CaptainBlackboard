//main.cpp
#include "my_hack.h"
#include "3rd_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char* argv[])
{
  _3rd_lib_func();

  printf("TAG: log printed from main.\n");
//  std::cout << "SSS" << std::endl;

  return 0;
}
