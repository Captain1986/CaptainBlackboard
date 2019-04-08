# Makefile

GIT_COMMIT_SHA1 = `git log -n 1 | head -n 1 | cut -d ' ' -f 2`

# 编译参数: Git commit SHA1
CFLAGS = -DGIT_COMMIT_SHA1=\"$(GIT_COMMIT_SHA1)\"

# 编译参数：如优化等级，调试信息，打开所有告警等等
CFLAGS += -O2 -g -Wall -std=c++11

a.out : main.cpp sdk.cpp
	g++ $^ $(CFLAGS) -o $@
  
.PHONY: clean

clean:
	rm a.out
