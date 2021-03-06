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
	std::cout << "Sposob nr 1" << std::endl;
	simpleWay(img1, img2);
	std::cout << "Nacisnij enter zeby kontynuowac" << std::endl;
	getchar();

	// SPOSOB NR 2
	std::cout << "Sposob nr 2 - algorytm genetyczny" << std::endl;
	Genetic g(img1, img2);
	g.mainLoop();

	getchar();
	getchar();
	cvWaitKey(2);
	return 0;
}