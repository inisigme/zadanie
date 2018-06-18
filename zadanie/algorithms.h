#pragma once
#include "stdafx.h"

typedef struct vec2 {
	float x, y;
};

vec2 findMiddle(Mat img);
uint detectScale(Mat img);
float detectRotation(Mat img);
vec2 detectLocation(Mat img);
float znajdzDopasownaie(Mat img1, Mat img2);
void roznice(Mat img1, Mat img2);
Mat scaleImg(Mat img, float scale);
void translateImg(Mat img, vec2 vec);
Mat rotateImgR(Mat img, vec2 point, float angle);
void rozniceKolorowany(Mat img1, Mat img2, Mat out);