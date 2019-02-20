//main.cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>
#include <float.h>
#include "timer.h"
#include "search_best.h"

#define FACENUM      (1000*1000) // 底库中存有100万张人脸特征向量
#define FEATSIZE           (512) // 每个人脸特征向量的维度是512维

int main(int argc, char* argv[])
{
  // 1.定义当前脸的特征，并初始化
  float vectorA[FEATSIZE];
  for(int i = 0; i < FEATSIZE; i++) {
      vectorA[i] = static_cast<float>(FACENUM/2*FEATSIZE + i) / (FACENUM * FEATSIZE);
  }

  // 2.定义底库中所有脸的特征向量，并初始化
  float* pDB = nullptr;
  try {
      pDB = new float[FACENUM*FEATSIZE];
  } catch (...) {
      std::cout << "out of memory\n";
  }

  for(int i = 0; i < FACENUM; i++) {
      for(int j = 0; j < FEATSIZE; j++) {
          pDB[i*FEATSIZE+j] = static_cast<float>(i*FEATSIZE + j) / (FACENUM * FEATSIZE);
      }
  }

  // 3.定义计数器并开始计时
  Timer t;

  int best_index = SearchBest(vectorA, FEATSIZE, pDB, FACENUM*FEATSIZE);

  // 4.打印结果
  std::cout << "Best face index is: " << best_index << std::endl;
  std::cout << "Find the best face index eat: " << t.elapsed_micro() << "us" << std::endl;
  std::cout << "PER Cosine_similarity call eat: " << t.elapsed_nano() / FACENUM << "ns" << std::endl;

  // 5.释放分配的内存，防止内存泄露
  delete [] pDB;

  return 0;
}
