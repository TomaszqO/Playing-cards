#pragma once
#ifndef  QUALITY_IMPROVEMENT_H
#define QUALITY_IMPROVEMENT_H

//#include <opencv2/opencv.hpp>
const int N = 9;
using namespace cv;

enum FILTRATION_TYPE {
	LOW_PASS,
	HIGH_PASS,
	UNSHARP_MASK
};

void InsertionSort(int ar[], const int & n);

//v1 chanel
Mat median1(Mat &Img, int r, const  int index);

Mat to1ChannelGray(Mat & img);

Mat& adaptiveThresholding(Mat& src, const int & r, const double & k);

Mat & filter2D(Mat& src, double* kernel, int kernelSize, double coeff, FILTRATION_TYPE FILTER);

Mat& binarize(Mat & src, int threshold);

Mat & inverseBinarize(Mat & img,int threshold);

Mat & histogramStretching(Mat & src);

Mat& erode(Mat & img);

Mat& dilate(Mat & img);

Mat& open(Mat& Img) {
	return dilate(erode(Img));
}

Mat& close(Mat & img) {
	return erode(dilate(img));
}
#endif // ! QUALITY_IMPROVEMENT_H
