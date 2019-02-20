#include <assert.h>
#include <cmath>
#include <float.h>
#include <climits>
#include "cosine_similarity.h"
#include "search_best.h"

// Step 1, g++ main.cpp search_best.cpp cosine_similarity.cpp -std=c++11
// Step 2, g++ main.cpp search_best.cpp cosine_similarity.cpp -std=c++11 -O3 -Ofast -ffast-math
int SearchBest(const float* pVecA, const int lenA, const float* pVecDB, const int lenDB)
{
    assert(lenDB%lenA == 0);
	const int featsize = lenA;
	const int facenum  = lenDB / lenA;

	int best_index = - INT_MAX;
	float best_similarity = - FLT_MAX;
	for(int i = 0; i < facenum; i++) {
		float similarity = Cosine_similarity(pVecA, pVecDB + i*featsize, featsize);
		if(similarity > best_similarity) {
			best_similarity = similarity;
			best_index = i;
		}
	}

    return best_index;
}
