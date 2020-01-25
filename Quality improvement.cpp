#include "stdafx.h"

using namespace cv;
using namespace std;

Mat& adaptiveThresholding(Mat& src, const int & r, const double & k ) { //savuola method
	cout << "Adaptive thresholding, Savuola method.\nProcessing...\n";
	Mat tempImg(src.rows, src.cols, CV_8UC1, Scalar(0));
	int C = 128;//for grayscale imgs
	double mean, std;
	int R = (r - 1) / 2;
	int rowsMax = src.rows - 1 - R;
	int colsMax = src.cols - 1 - R;
	int rSize = r*r;
	int localThresh;
	for (int i = r - 1; i < rowsMax; i++) {
		for (int j = r - 1; j < colsMax; j++) {
			mean = 0;
			for (int i1 = 0; i1 < r; i1++) {
				for (int j1 = 0; j1 < r; j1++) {
					mean+= int(src.at<uchar>(i - R + i1, j - R + j1));
				}
			}
			mean /= rSize;
			std = 0;
			for (int i1 = 0; i1 < r; i1++) {
				for (int j1 = 0; j1 < r; j1++) {
					std+= pow((int(src.at<uchar>(i - R + i1, j - R + j1)) - mean),2);
				}
			}
			std /= rSize;
			std = sqrt(std);
			localThresh = mean * (1 + (k*(std / C - 1)));
			if ((int)(src.at<uchar>(i, j) <= localThresh + 35))
				tempImg.at<uchar>(i, j) = 255;
			else
				tempImg.at<uchar>(i, j) = 0;
		}
	}
	src = tempImg;
	return src;
}

Mat & histogramStretching(Mat & src) {
	int min = 255, max = 0;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) > max) max = src.at<uchar>(i, j);
			if (src.at<uchar>(i, j) < min) min = src.at<uchar>(i, j);
		}
	}

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			src.at<uchar>(i, j) -= min;
		}
	}
	double c = 255 / (max - min);
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			src.at<uchar>(i, j)  = int(src.at<uchar>(i, j) * c);
		}
	}
	return src;
}

Mat & inverseBinarize(Mat & src, int threshold) {
	std::cout << "Inverse binarization.\nProcessing...\n";
	int rowsMax = src.rows;
	int colsMax = src.cols;
	for (int i = 0; i < rowsMax; i++) {
		for (int j = 0; j < colsMax; j++) {
			if (src.at<uchar>(i, j) < threshold) {
				src.at<uchar>(i, j) = 255;
			}
			else src.at<uchar>(i, j) = 0;
		}
	}
	return src;
}

Mat& binarize(Mat & src, int threshold) {
	//tylko 1 kanalowe ma przyjmowac, poprawic to!
	int rowsMax = src.rows;
	int colsMax = src.cols;
	for (int i = 0; i < rowsMax; i++) {
		for (int j = 0; j < colsMax; j++) {
			if (src.at<uchar>(i, j) > threshold) {
				src.at<uchar>(i, j) = 255;
			}
			else src.at<uchar>(i, j) = 0;
		}
	}
	return src;
}

void InsertionSort(int ar[], const int & n)
{
	int insert, j;
	for (int i = 1; i < n; i++)
	{
		insert = ar[i];
		j = i - 1;
		while (j >= 0 && insert < ar[j])
		{
			ar[i] = ar[j];
			ar[j] = insert;
			i = j;
			j--;
		}
	}
}

Mat  median1(Mat &Img, int r, const  int index) {
	std::cout << "Median filter.\nProcessing...\n";
	cv::Mat  Temp(Img.rows, Img.cols, CV_8UC1, Scalar(0));
	int R = (r - 1) / 2;
	int rowsMax = Img.rows - 1 - R;
	int colsMax = Img.cols - 1 - R;
	std::vector<int>grayChannel;
	int *gray = new int[r*r];
	int it = 0;
	for (int i = r - 1; i < rowsMax; i++) {
		for (int j = r - 1; j < colsMax; j++) {
			it = 0;
			for (int i1 = 0; i1 < r; i1++) {
				for (int j1 = 0; j1 < r; j1++) {
					gray[it] = Img.at<uchar>(i - R + i1, j - R + j1);
					it++;
				}
			}
			InsertionSort(gray, it);
			Temp.at<uchar>(i, j) = gray[index];
		}
	}
	delete[] gray;
	Img = Temp;
	return Img;
}

Mat to1ChannelGray(Mat & img) {
	int rowsMax = img.rows;
	int colsMax = img.cols;
	Mat dst(rowsMax, colsMax, CV_8UC1);
	Mat_ <Vec3b> I = img;
	for (int i = 0; i < rowsMax; i++) {
		for (int j = 0; j < colsMax; j++) {
			dst.at<uchar>(i, j) =(int) (0.11*I(i, j)[0] + 0.59*I(i, j)[1] + 0.3*I(i, j)[2]);
		}
	}
	return dst;
}

Mat & filter2D(Mat& src, double* kernel, int kernelSize, double coeff, FILTRATION_TYPE FILTER) {
	if (FILTER == FILTRATION_TYPE::HIGH_PASS) {
		std::cout << "High pass filter.\nProcessing...\n";
	}
	else if (FILTER == FILTRATION_TYPE::LOW_PASS) {
		std::cout << "Low pass filter.\nProcessing...\n";
	}
	else if (FILTER == FILTRATION_TYPE::UNSHARP_MASK) {
		std::cout << "Unsharp mask filter.\nProcessing...\n";
	}
	cv::Mat Temp(src.rows, src.cols, CV_8UC1, Scalar(0));
	int R = (kernelSize - 1) / 2;//3 dla 3x3
	double temp;
	int kernellterator;
	for (int i = R; i < src.rows - 1 - R; i++) {
		for (int j = R; j < src.cols - 1 - R; j++) {
			temp = 0;
			kernellterator = 0;
			for (int kx = 0; kx < kernelSize; kx++) {
				for (int ky = 0; ky < kernelSize; ky++) {
					temp += src.at<uchar>(i - R + kx, j - R + ky) * kernel[kernellterator] ;//+ i - w zaleznosci od srodka maski
					kernellterator++;
				}
			}
			temp *= coeff;
			//cout <<(int) (src.at<uchar>(i, j)) << "     " << temp << endl;

			if (FILTER == FILTRATION_TYPE::UNSHARP_MASK) {
				if (-temp + 2 * (int)(src.at<uchar>(i, j)) > 255)
					Temp.at<uchar>(i, j) = 255;
				else if (-temp + 2 * (int)(src.at<uchar>(i, j)) < 0)
					Temp.at<uchar>(i, j) = 0;
				else
					Temp.at<uchar>(i, j) = int(-temp + 2* (int)(src.at<uchar>(i, j)));
			}
			else if (FILTER == FILTRATION_TYPE::HIGH_PASS) {
				if (temp + (int)(src.at<uchar>(i, j)) > 255)
					Temp.at<uchar>(i, j) = 255;
				else if (temp + (int)(src.at<uchar>(i, j)) < 0)
					Temp.at<uchar>(i, j) = 0;
				else
					Temp.at<uchar>(i, j) = (int)(temp + (int)(src.at<uchar>(i, j)));
			}
			else if (FILTER == FILTRATION_TYPE::LOW_PASS) {
				if (temp  > 255)
					Temp.at<uchar>(i, j) = 255;
				else if (temp< 0)
					Temp.at<uchar>(i, j) = 0;
				else
					Temp.at<uchar>(i, j) = (int)temp;
			}
		}
	}
	src = Temp;
	return src;
}

Mat& erode(Mat & img) {
	cv::Mat Temp(img.size(), CV_8UC1);
	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {

			if (img.at<uchar>(i - 1, j - 1) == 0 || img.at<uchar>(i - 1, j) == 0 || img.at<uchar>(i - 1, j + 1) == 0 ||
				img.at<uchar>(i, j - 1)== 0 || img.at<uchar>(i, j) == 0 || img.at<uchar>(i, j + 1) == 0 ||
				img.at<uchar>(i + 1, j - 1) == 0 || img.at<uchar>(i + 1, j) == 0 || img.at<uchar>(i + 1, j + 1) == 0) {
				Temp.at<uchar>(i, j) = 0;
			}
			else {
				Temp.at<uchar>(i, j) = 255;
			}
		}
	}
	img = Temp;
	return img;
}

Mat& dilate(Mat & img) {
	cv::Mat Temp(img.size(), CV_8UC1);
	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			//if ( img.at<uchar>(i - 1, j) == 255  ||
			//	img.at<uchar>(i, j - 1) == 255 || img.at<uchar>(i, j) == 255 || img.at<uchar>(i, j + 1) == 255 ||
			//	 img.at<uchar>(i + 1, j) == 255) {
			//	Temp.at<uchar>(i, j) = 255;
			//}
			//else {
			//	Temp.at<uchar>(i, j) = 0;
			//}
			if (img.at<uchar>(i - 1, j - 1) == 255 || img.at<uchar>(i - 1, j) == 255 || img.at<uchar>(i - 1, j + 1) == 255 ||
				img.at<uchar>(i, j - 1) == 255 || img.at<uchar>(i, j) == 255 || img.at<uchar>(i, j + 1) == 255 ||
				img.at<uchar>(i + 1, j - 1) == 255 || img.at<uchar>(i + 1, j) == 255 || img.at<uchar>(i + 1, j + 1) == 255) {
				Temp.at<uchar>(i, j) = 255;
			}
			else {
				Temp.at<uchar>(i, j) = 0;
			}
		}
	}
	img = Temp;
	return img;
}
