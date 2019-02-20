#ifndef _COSINE_SIMILARITY_
#define _COSINE_SIMILARITY_

#include <cmath>
#include <float.h>
#include "cosine_similarity.h"

template <typename T>
T Cosine_similarity(const T* vectorA, const T* vectorB, const int len)
{
    T mult_add = 0.0f;
    T a_norm2  = 0.0f;
    T b_norm2  = 0.0f;

    for(int i = 0; i < len; i++) {
        mult_add += vectorA[i] * vectorB[i];
        a_norm2  += vectorA[i] * vectorA[i];
        b_norm2  += vectorB[i] * vectorB[i];
    }

    const T similarity = mult_add / (sqrt(a_norm2 * b_norm2) + FLT_MIN);

    return similarity;
}

#endif // !_COSINE_SIMILARITY_

