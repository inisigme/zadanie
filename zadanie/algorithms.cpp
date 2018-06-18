#include "stdafx.h"
#include "algorithms.h"


uint detectScale(Mat img) {
	uint licznik = 0;
	for (int i = 0; i < img.rows; i++)
	{
		auto Mi = img.ptr<unsigned char>(i);
		for (int j = 0; j < img.cols; j++) {
			if (Mi[j] != 0) licznik++;
		}
	}
	return licznik;
}



vec2 detectLocation(Mat img) {
	uint Xsum = 0;
	uint Ysum = 0;
	uint amount = 0;
	uint licznik = 0;
	for (int i = 0; i < img.rows; i++)
	{
		auto Mi = img.ptr<unsigned char>(i);
		for (int j = 0; j < img.cols; j++)
			if (Mi[j] == 255) {
				Xsum += i;
				Ysum += j;
				amount++;
			}
	}
	vec2 out{ (float)Xsum / (float)amount , (float)Ysum / (float)amount };
	return out;
}

float znajdzDopasownaie(Mat img1, Mat img2)
{
	unsigned int zgodnosc = 0;
	for (int i = 0; i < img1.rows; i++)
	{
		auto Mi1 = img1.ptr<unsigned char>(i);
		auto Mi2 = img2.ptr<unsigned char>(i);
		for (int j = 0; j < img1.cols; j++) {
			if (Mi1[j] == Mi2[j]) { 
				zgodnosc++;
			}
		}
	}
	return (float)zgodnosc / (float)(img1.rows * img1.cols);
}




float detectRotation(Mat src) {
	Mat dst, cdst;

	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, CV_GRAY2BGR);

	//float finalAngle = 0;
	float finalAngle2 = 0;
	//float finalAngleX = 0;
	//float finalAngleY = 0;

	std::vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 40, 0, 0);

	for (size_t i = 0; i < lines.size() && i < 8; i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
	//	finalAngle += ((float)pt1.x - (float)pt2.x) / ((float)pt1.y - (float)pt2.y);
	//	finalAngleX = (float)pt1.x - (float)pt2.x;
	//	finalAngleY = (float)pt1.y - (float)pt2.y;
		finalAngle2 += atanf(((float)pt1.y - (float)pt2.y) / ((float)pt1.x - (float)pt2.x)) * 180 / 3.4169;
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}

	//float angleOut = cvFastArctan((float)finalAngle / (float)lines.size(), 1.0f);
	return finalAngle2 / 8.0f;
}

void roznice(Mat img1, Mat img2) {
	Mat out = cv::Mat::zeros(img1.size(), CV_8UC4);
	for (int i = 0; i < img1.rows; i++)
	{
		auto Mi1 = img1.ptr<unsigned char>(i);
		auto Mi2 = img2.ptr<unsigned char>(i);
		auto Mi3 = out.ptr<unsigned char>(i);
		for (int j = 0; j < img1.cols; j++) {
			auto o = Mi1[j] + Mi2[j];
			Mi1[j] = o / 2;
		}
	}
	imshow("ROZNICE", img1);
}




Mat scaleImg(Mat img, float scale) {
	auto bRows = img.rows;
	auto bCols = img.cols;
	resize(img, img, cv::Size(0, 0), scale, scale, INTER_NEAREST);
	int top, bot, left, right;
	top = (bRows - img.rows) / 2;
	bot = bRows - img.rows - top;
	left = (bCols - img.cols) / 2;
	right = bCols - img.cols - left;
	copyMakeBorder(img, img, top, bot, left, right, BORDER_CONSTANT);
	return img;
}

void translateImg(Mat img, vec2 vec) {
	Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, vec.x, 0, 1, vec.y);
	warpAffine(img, img, trans_mat, img.size());
}

Mat rotateImgR(Mat img, vec2 point, float angle)
{
	Mat dst(img);
	cv::Point2f pc(point.x, point.y);
	cv::Mat r = cv::getRotationMatrix2D(pc, (double)angle, 1.0);
	cv::warpAffine(img, dst, r, img.size());
	return dst;
}




void rozniceKolorowany(Mat img1, Mat img2, Mat out) {
	for (int i = 0; i < img1.rows; i++)
	{
		auto Mi1 = img1.ptr<unsigned char>(i);
		auto Mi2 = img2.ptr<unsigned char>(i);
		unsigned char * outptr = (unsigned char*)(out.data);
		for (int j = 0; j < img1.cols; j++) {
			if (Mi1[j] == 255 && Mi2[j] == 255) {
				out.at<cv::Vec3b>(i, j)[0] = 255;
			}
			else if (Mi1[j] == 255 && Mi2[j] == 0) {
				out.at<cv::Vec3b>(i, j)[1] = 255;
			}
			else if (Mi1[j] == 0 && Mi2[j] == 255) {
				out.at<cv::Vec3b>(i, j)[2] = 255;
			}
			else if (Mi1[j] == 0 && Mi2[j] == 0) {
				out.at<cv::Vec3b>(i, j)[0] = 0;
			}
		}
	}
	imshow("KOLOROWANY", out);
}