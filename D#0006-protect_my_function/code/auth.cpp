//auth.cpp
#include "auth.h"

AuthRet get_auth_result(const char* key)
{

  AuthRet ret = {.iSuccess = -1,
                 .magic    = -1
                };

  if(!strcmp(key, "a valid key")) {
     printf("auth successed.\n");
     ret.iSuccess = 0;
  } else {
     printf("auth failed.\n");
     ret.iSuccess = -1;
  }

  ret.magic = key[0] + key[strlen(key) - 1];

  return ret;
}
