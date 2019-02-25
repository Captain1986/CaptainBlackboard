#ifndef _SEARCHBEST_
#define _SEARCHBEST_

#include <assert.h>
#include <cmath>
#include <float.h>
#include <climits>
#include "cosine_similarity.h"

// Step 1, g++ main.cpp search_best.cpp cosine_similarity.cpp -std=c++11
// Step 2, g++ main.cpp search_best.cpp cosine_similarity.cpp -std=c++11 -O3
// Step 3, g++ main.cpp search_best.cpp cosine_similarity.cpp -std=c++11 -O3 -Ofast -ffast-math
template <typename T>
int SearchBest(const T* __restrict__ const pVecA,  // 待搜索的单个特征向量首地址
               const int lenA,  // 待搜索特征向量长度(1 x 单个特征维数)
               const T* __restrict__ const pVecDB, // 底库首地址
               const int lenDB) // 底库长度(特征个数 x 单个特征维数)
{
    assert(lenDB%lenA == 0);
    const int featsize = lenA;
    const int facenum  = lenDB / lenA;

    int best_index = - INT_MAX;
    T best_similarity = - FLT_MAX;
// Step 5, 加上OpenMP
//GCC很聪明，OpenMP默认线程数就是多核处理器的核心数量，不必显示指定
//OpenMP起线程，收回线程也是有开销的，所以要合理安排每个线程的任务量大小，不宜放入内层for循环（任务量太小划不来）
//#pragma omp parallel for num_threads(8)
#pragma omp parallel for
    for(int i = 0; i < facenum; i++) {
        // 普通C++代码实现的余弦相似度计算
        T similarity = Cosine_similarity(pVecA, pVecDB + i*featsize, featsize);
        // 使用向量化代码实现的余弦相似度计算
        //T similarity = Cosine_similarity_avx(pVecA, pVecDB + i*featsize, featsize);
        if(similarity > best_similarity) {
            best_similarity = similarity;
            best_index = i;
        }
    }

    return best_index;
}

#endif //!_SEARCHBEST_
