#include "stdafx.h"

using namespace std;

Mat segmenting(Mat & src) {
	Mat dst(src.rows, src.cols, CV_8UC3, Scalar(0, 0, 0));
	Mat_ <Vec3b> I = dst;
	srand(time(NULL));
	int a = rand() % 255;
	int b = rand()% 255;
	int c = rand() % 255;
	Vec3b newColor;

	for (int i = 1; i < src.rows-1; i++) {
		for (int j = 1; j < src.cols-1; j++) {
			if ((int)(src.at<uchar>(i,j)) == 255) {
				newColor[0] = rand() % 255;
				newColor[1] = rand() % 255;
				newColor[2] = rand() % 255;
				floodFill(dst, src, i, j, (255, 255, 255), newColor );
			}
		}
	}
	return dst;
}

void floodFill(Mat& dst3Chan, Mat& src1Chan, int x, int y, Scalar oldColor, Vec3b newColor) {
	Mat_ <Vec3b> I = dst3Chan;
	int x_, y_;
	Point p(x, y);
	queue <Point> kolejka;
	kolejka.push(p);
	while (!kolejka.empty()) {
		x_ = kolejka.front().x;//coordins o fnew color pixel
		y_ = kolejka.front().y;
		kolejka.pop();
		if ((int)(src1Chan.at<uchar>(x_,y_)) == 255) {
			src1Chan.at<uchar>(x_, y_) = 150;
			I(x_, y_)[0] = newColor[0];
			I(x_, y_)[1] = newColor[1];
			I(x_, y_)[2] = newColor[2];
			kolejka.push(Point(x_, y_ - 1));//left
			kolejka.push(Point(x_, y_ + 1));//prawo
			kolejka.push(Point(x_-1, y_ ));//gora
			kolejka.push(Point(x_+1, y_ ));//dol
		}
	}
}
