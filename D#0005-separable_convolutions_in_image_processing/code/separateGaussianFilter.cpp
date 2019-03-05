//separateGaussianFilter.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include "separateGaussianFilter.h"

using namespace cv;

void separateGaussianFilter(const Mat &src, Mat &dst, int ksize, double sigma)
{
    CV_Assert(src.channels() == 3); // 只处理三通道图像
    // 生成一维的高斯滤波模板
    double *matrix = new double[ksize];
    double sum = 0;
    int origin = ksize / 2;
    for (int i = 0; i < ksize; i++) {
        // 高斯函数前的常数可以不用计算，会在归一化的过程中给消去
        double g = exp(-(i - origin) * (i - origin) / (2 * sigma * sigma));
        sum += g;
        matrix[i] = g;
    }
    // 归一化
    for (int i = 0; i < ksize; i++) {
        matrix[i] /= sum;
    }
    // 将模板应用到图像中
    int border = ksize / 2;
    copyMakeBorder(src, dst, border, border, border, border, BorderTypes::BORDER_REFLECT);
    int channels = dst.channels();
    int rows = dst.rows - border;
    int cols = dst.cols - border;
    // 水平方向
    for (int i = border; i < rows; i++) {
        for (int j = border; j < cols; j++) {
            double sum[3] = { 0 };
            for (int k = -border; k <= border; k++)    {
                 Vec3b rgb = dst.at<Vec3b>(i, j + k);
                 sum[0] += matrix[border + k] * rgb[0];
                 sum[1] += matrix[border + k] * rgb[1];
                 sum[2] += matrix[border + k] * rgb[2];
            }
            Vec3b rgb = { static_cast<uchar>(sum[0]), static_cast<uchar>(sum[1]), static_cast<uchar>(sum[2]) };
            dst.at<Vec3b>(i, j) = rgb;
        }
    }

    // 竖直方向
    for (int i = border; i < rows; i++) {
        for (int j = border; j < cols; j++)    {
            double sum[3] = { 0 };
            for (int k = -border; k <= border; k++) {
                 Vec3b rgb = dst.at<Vec3b>(i + k, j);
                 sum[0] += matrix[border + k] * rgb[0];
                 sum[1] += matrix[border + k] * rgb[1];
                 sum[2] += matrix[border + k] * rgb[2];
            }
            Vec3b rgb = { static_cast<uchar>(sum[0]), static_cast<uchar>(sum[1]), static_cast<uchar>(sum[2]) };
            dst.at<Vec3b>(i, j) = rgb;
        }
    }

    delete[] matrix;
}
