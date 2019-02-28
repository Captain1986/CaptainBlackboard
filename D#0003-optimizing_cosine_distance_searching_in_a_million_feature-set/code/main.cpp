//main.cpp
#include <iostream>
#include <malloc.h>
#include "timer.h"
#include "search_best.h"

#define ALGIN               (32) // 使用SIMD需要内存对齐，128bit的指令需要16位对齐，256bit的指令需要32位对齐
#define FACENUM      (1000*1000) // 底库中存有100万张人脸特征向量
//#define FEATSIZE           (512) // 每个人脸特征向量的维度是512维，每一维是一个DType类型的浮点数
//Step 11，用PCA做特征选择，压缩512维到256维
#define FEATSIZE             (256) // 每个人脸特征向量的维度是256维，每一维是一个DType类型的浮点数

// Step 4, double-->float(在我的电脑上，sizeof(float)==4，sizeof(double)==8, sizeof(short)==2, sizeof(int)==4
//typedef float DType;
// Step 12, float-->unsigned short，定点化
typedef float DType;

float calcL(const DType * const pVec, const int len)
{
   float l = 0.0f;

   for(int i = 0; i < len; i++) {
      l += pVec[i] * pVec[i];
   }

   return sqrt(l) + FLT_MIN;
}

int main(int argc, char* argv[])
{
  // 1.定义当前脸的特征，并初始化
  __attribute__((aligned(ALGIN))) DType vectorA[FEATSIZE];
  for(int i = 0; i < FEATSIZE; i++) {
      vectorA[i] = static_cast<DType>(FACENUM/2*FEATSIZE + i) / (FACENUM * FEATSIZE);
  }

  // 模归一化
  const float l = calcL(vectorA, FEATSIZE);
  for(int i = 0; i < FEATSIZE; i++) {
      vectorA[i] /= l;
  }

  // 2.定义底库中所有脸的特征向量，并初始化
  // 为了使用SIMD优化，使用memalign申请对齐了的内存，牺牲了代码的可移植性
  DType* pDB = reinterpret_cast<DType*>(memalign(ALGIN, sizeof(DType)*FACENUM*FEATSIZE));
  if(!pDB) {
      std::cout << "out of memory\n";
      return -1;
  }

  // 验证内存是否对齐
  // printf("vectorA[%p], pDB[%p].\n", vectorA, pDB);

  for(int i = 0; i < FACENUM; i++) {
      for(int j = 0; j < FEATSIZE; j++) {
          pDB[i*FEATSIZE+j] = static_cast<DType>(i*FEATSIZE + j) / (FACENUM * FEATSIZE);
      }

      // 模归一化
      const float norm = calcL(pDB + i*FEATSIZE, FEATSIZE);
      for(int j = 0; j < FEATSIZE; j++) {
          pDB[i*FEATSIZE+j] /= norm;
      }
  }

  // 3.定义计数器并开始计时
  Timer t;

  int best_index = SearchBest(static_cast<DType*>(vectorA), FEATSIZE, pDB, FACENUM*FEATSIZE);

  // 4.打印结果
  std::cout << "Best face index is: " << best_index << std::endl;
  std::cout << "Find the best face index eat: " << t.elapsed_micro() << "us" << std::endl;
  std::cout << "PER Cosine_similarity call eat: " << t.elapsed_nano() / FACENUM << "ns" << std::endl;
  //printf("double[%d], float[%d], short[%d], int[%d].\n", (int)sizeof(double), (int)sizeof(float), (int)sizeof(short), (int)sizeof(int));

  // 5.释放分配的内存，防止内存泄露
  // memalign分配的内存也可以用free释放
  free(pDB);

  return 0;
}
