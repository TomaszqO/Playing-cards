#pragma once
#ifndef SEGMENT
#define SEGMENT
#include "stdafx.h"

Mat segmenting(Mat & src);

void floodFill(Mat& dst3Chan, Mat& src1Chan, int x, int y, Scalar OldColor, Vec3b newColor);
#endif