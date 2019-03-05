#!/bin/bash
g++ main.cpp GaussianFilter.cpp separateGaussianFilter.cpp -std=c++11 `pkg-config --libs --cflags opencv`
