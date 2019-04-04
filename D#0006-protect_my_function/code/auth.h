//auth.h
#ifndef _AUTH_
#define _AUTH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagAuthRet {
  int  iSuccess;
  long magic;
} AuthRet;

AuthRet get_auth_result(const char* key);

#endif // !_AUTH_
