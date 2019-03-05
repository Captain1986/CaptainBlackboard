//separateGaussianFilter.h
#ifndef _SEPARATEGAUSSIANFILTER_
#define _SEPARATEGAUSSIANFILTER_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void separateGaussianFilter(const Mat &src, Mat &dst, int ksize, double sigma);

#endif // !_SEPARATEGAUSSIANFILTER_
