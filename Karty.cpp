// Karty.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
using namespace cv;

template<typename int r>
void show(double ar[][r], string s) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			cout << ar[i][j];
		}
	}
}
queue <int> kolejka;
int main()
{
	Menu();

	///double t1[3][3]{ {} };
	//double t2[2][2]{ 4,2,5,1231 };
	//show(t1, "asdasd");
	//show(t2, "asdas");

	cin.get();
    return 0;
}

