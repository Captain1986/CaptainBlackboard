//GaussianFilter.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include "GaussianFilter.h"

using namespace cv;

void GaussianFilter(const Mat &src, Mat &dst, int ksize, double sigma)
{
    CV_Assert(src.channels() == 3); // 只处理三通道图像
    const static double pi = 3.1415926;
    // 根据窗口大小和sigma生成高斯滤波器模板
    // 申请一个二维数组，存放生成的高斯模板矩阵
    double **templateMatrix = new double*[ksize];
    for (int i = 0; i < ksize; i++) {
         templateMatrix[i] = new double[ksize];
    }
    int origin = ksize / 2; // 以模板的中心为原点
    double x2, y2;
    double sum = 0;
    for (int i = 0; i < ksize; i++) {
         x2 = pow(i - origin, 2);
         for (int j = 0; j < ksize; j++) {
              y2 = pow(j - origin, 2);
              // 高斯函数前的常数可以不用计算，会在归一化的过程中给消去
              double g = exp(-(x2 + y2) / (2 * sigma * sigma));
              sum += g;
              templateMatrix[i][j] = g;
         }
    }
    
    for (int i = 0; i < ksize; i++) {
         for (int j = 0; j < ksize; j++) {
             templateMatrix[i][j] /= sum;
  //           cout << templateMatrix[i][j] << " ";
         }
  //       cout << endl;
    }

    // 将模板应用到图像中
    int border = ksize / 2;
    copyMakeBorder(src, dst, border, border, border, border, BorderTypes::BORDER_REFLECT);
    int channels = dst.channels(); // 3
    int rows = dst.rows - border;
    int cols = dst.cols - border;
    for (int i = border; i < rows; i++) {
        for (int j = border; j < cols; j++) {
            double sum[3] = { 0 };
            for (int a = -border; a <= border; a++) {
                for (int b = -border; b <= border; b++)    {
                     Vec3b rgb = dst.at<Vec3b>(i + a, j + b);
                     auto k = templateMatrix[border + a][border + b];
                     sum[0] += k * rgb[0];
                     sum[1] += k * rgb[1];
                     sum[2] += k * rgb[2];
                }
            }
            Vec3b rgb = { static_cast<uchar>(sum[0]), static_cast<uchar>(sum[1]), static_cast<uchar>(sum[2]) };
            dst.at<Vec3b>(i, j) = rgb;
        }
    }

    // 释放模板数组
    for (int i = 0; i < ksize; i++)
        delete[] templateMatrix[i];
    delete[] templateMatrix;
}

