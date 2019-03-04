#!/bin/bash
g++ main.cpp -std=c++11 `pkg-config --libs --cflags opencv`
