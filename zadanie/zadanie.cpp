// zadanie.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "algorithms.h"
#include "Genetic.h"

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

	vec2 p1, p2, translation;

	Mat dst(img1);

	float scale = (float)detectScale(img2) / (float)detectScale(dst) + 0.035;
	//float scale = 0.88;
	dst = scaleImg(dst, scale);
	std::cout << "SCALE :       " << scale << std::endl;


	float rotation = detectRotation(dst) - detectRotation(img2) - 1.5;
	p1 = detectLocation(dst);
	dst = rotateImgR(dst, p1, rotation);

	std::cout << "Rotation:       " << rotation << std::endl;


	p1 = detectLocation(dst);
	p2 = detectLocation(img2);
	translation = { p2.y - p1.y - 3, p2.x - p1.x - 1 };
	translateImg(dst, translation);

	std::cout << "translation:   " << translation.x << "," << translation.y << std::endl;




	cv::Mat kolorowany = cv::Mat::zeros(img1.rows, img1.cols, CV_8UC3);
	rozniceKolorowany(img2, dst, kolorowany);


	std::cout << "DOPASOWANIE:   " << znajdzDopasownaie(dst, img2) << std::endl;
	roznice(dst, img2);
	cvWaitKey(1);
	getchar();

	Genetic g(img1, img2);
	g.mainLoop();
	getchar();
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