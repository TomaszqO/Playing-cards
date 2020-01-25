#pragma once
#ifndef UI
#define UI

enum PROCESS {
	EXIT,
	CONTINUE
};
void Menu();
void processImage(Mat & img);
void rankFilter(Mat & img);
void filterSharp(Mat & img);
void binarization(Mat & img);
void inverseBinarization(Mat & img);
void adaptiveBinarization(Mat & img);///write
#endif