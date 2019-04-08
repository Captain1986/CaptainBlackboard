//sdk.cpp
#include "sdk.h"

int sdk_func(void* p)
{

  // 打印git commit sha1，和build_time信息，便于问题回溯
  printf("build_sha1:\t%s\nbuild_time:\t%s %s\n",
          GIT_COMMIT_SHA1, __DATE__, __TIME__);

  // 这里可以做sdk的事情

  return 0;
}

