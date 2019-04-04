//sdk.cpp
#include "sdk.h"
#include "auth.h"

int sdk_add(const int a, const int b, const char* key)
{
  int sum = 0;

  AuthRet ret = get_auth_result(key);

  if(ret.magic == key[0] + key[strlen(key) - 1]) {
     if(ret.iSuccess == 0) {
        printf("sdk think auth ok.\n");
        sum = a + b;
     } else {
        printf("sdk think auth bad(magic number check ok).\n");
        sum = 0;
     }
  } else {
     printf("sdk think auth bad(magic number check fail).\n");
     sum = 0;
  }

  return sum;
}
