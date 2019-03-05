//main.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include "timer.h"
#include "GaussianFilter.h"
#include "separateGaussianFilter.h"

int main(int argc, char* argv[])
{
  cv::Mat src = cv::imread(argv[1]);
  cv::imshow("src", src);

  cv::Mat dst;

  int ksize = 11;
  double sigma = 0.8;

  // 定义计数器并开始计时
  Timer t;
  GaussianFilter(src, dst, ksize, sigma);
  cv::imshow("GaussianFilter", dst);

  // 打印结果
  std::cout << "GaussianFilter eat: " << t.elapsed_micro() << "us" << std::endl;

  t.reset();
  separateGaussianFilter(src, dst, ksize, sigma);
  cv::imshow("separateGaussianFilter", dst);

  // 打印结果
  std::cout << "separateGaussianFilter eat: " << t.elapsed_micro() << "us" << std::endl;

  cv::waitKey(0);

  return 0;
}
