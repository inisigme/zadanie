// zadanie.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "algorithms.h"
#include "Genetic.h"
#include "SimpleWay.h"


int main(int argc, char *argv[])
{
	Mat img1, img2;

	img1 = imread("rekrutacja/img1.png");
	img2 = imread("rekrutacja/img2.png");
	cvtColor(img1, img1, CV_BGR2GRAY);
	threshold(img1, img1, 254, 255, THRESH_BINARY);

	cvtColor(img2, img2, CV_BGR2GRAY);
	threshold(img2, img2, 254, 255, THRESH_BINARY);

	bitwise_not(img1, img1);
	bitwise_not(img2, img2);

	// SPOSOB NR 1
	simpleWay(img1, img2);

	// SPOSOB NR 2
	Genetic g(img1, img2);
	g.mainLoop();
	
	
	
	
	
	getchar();
	getchar();
	cvWaitKey(2);
	return 0;
}

/*



std::cout << "%%%" << (float)detectScale(img2) <<"         " << (float)detectScale(img1) << std::endl;
std::cout << "Scale" << (float)detectScale(img2) / (float)detectScale(img1) << std::endl;
std::cout << "Location" << p1.x - p2.x << "," << p1.y - p2.y << std::endl;



Point pt1, pt2;
pt1.x = p1.x;
pt1.y = p1.y;
pt1.x = p1.x + translation.x;
pt1.y = p1.y + translation.y;

*/