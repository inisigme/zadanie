#include "stdafx.h"
#include "SimpleWay.h"

void simpleWay(Mat img1, Mat img2)
{

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
	cvWaitKey(1);
}
