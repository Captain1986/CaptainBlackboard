//GaussianFilter.h
#ifndef _GAUSSIANFILTER_
#define _GAUSSIANFILTER_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void GaussianFilter(const Mat &src, Mat &dst, int ksize, double sigma);

#endif // !_GAUSSIANFILTER_
