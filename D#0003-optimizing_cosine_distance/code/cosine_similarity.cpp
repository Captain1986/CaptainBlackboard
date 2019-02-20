#include <cmath>
#include <float.h>
#include "cosine_similarity.h"

float Cosine_similarity(const float vectorA[], const float vectorB[], const int len)
{
    float mult_add = 0.0f;
    float a_norm2  = 0.0f;
    float b_norm2  = 0.0f;

    for(int i = 0; i < len; i++) {
        mult_add += vectorA[i] * vectorB[i];
        a_norm2  += vectorA[i] * vectorA[i];
        b_norm2  += vectorB[i] * vectorB[i];
    }

    const float similarity = mult_add / (sqrt(a_norm2 * b_norm2) + FLT_MIN);

    return similarity;
}
