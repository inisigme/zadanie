#include "stdafx.h"
#include "SimpleWay.h"

void simpleWay(Mat img1, Mat img2)
{
	vec2 p1, p2, translation;
	Mat dst(img1);

	float scale = (float)detectScale(img2) / (float)detectScale(dst) + 0.035;
	dst = scaleImg(dst, scale);
	std::cout << "SCALE :       " << scale << std::endl;

	float rotation = detectRotation(dst) - detectRotation(img2);
	p1 = detectLocation(dst);
	dst = rotateImgR(dst, p1, rotation);

	std::cout << "Rotation:       " << rotation << std::endl;

	p1 = detectLocation(dst);
	p2 = detectLocation(img2);
	translation = { round(p2.y - p1.y), round(p2.x - p1.x) };
	translateImg(dst, translation);

	std::cout << "translation:   " << translation.x << "," << translation.y << std::endl;

	cv::Mat kolorowany = cv::Mat::zeros(img1.rows, img1.cols, CV_8UC3);
	rozniceKolorowany(img2, dst, kolorowany);

	std::cout << "DOPASOWANIE:   " << znajdzDopasownaie(dst, img2) << std::endl;
	cvWaitKey(1);
}
