#include "stdafx.h"
#include "Genetic.h"


void Genetic::evaluate(unsigned int iteration)
{
	float sum = 0.0;
	float amount = 0;
	unsigned int index = 0;
	float max = -1.0;
	for (unsigned int i = 0; i < pupulationSize; i++) {
		vec2 translation = { population[i].offsetX, population[i].offsetY };
		Mat dst(basicImage);
		dst = scaleImg(dst, population[i].scale);
		dst = rotateImgR(dst, detectLocation(dst), population[i].angle);
		translateImg(dst, translation);
		population[i].evaluation = znajdzDopasownaie(dst, toCompare);
		sum += population[i].evaluation;
		amount++;
		if (population[i].evaluation > max) {
			max = population[i].evaluation;
			index = i;
		}
	}
	actual = max;
	history[iteration % 20] = max;
	if (population[index].evaluation > best.evaluation)
		best = population[index];
	std::cout << "SREDNIA:    " << sum / amount << std::endl;
}

void Genetic::mutate()
{
	for (auto & one : population) {
		if (rand() % 1 == 0) {
			one.offsetX += rand() % 4 - 2;
			one.offsetY += rand() % 4 - 2;
			one.offsetX = one.offsetX > offsetMax ? offsetMax : one.offsetX;
			one.offsetX = one.offsetX < offsetMin ? offsetMin : one.offsetX;
			one.offsetY = one.offsetY > offsetMax ? offsetMax : one.offsetY;
			one.offsetY = one.offsetY < offsetMin ? offsetMin : one.offsetY;
			one.scale += ((float)rand() / (float)RAND_MAX - 0.5f) / 30.0f;
			one.scale = one.scale > scaleMax ? scaleMax : one.scale;
			one.scale = one.scale < scaleMin ? scaleMin : one.scale;
			one.angle += ((float)rand() / (float)RAND_MAX - 0.5f);
			one.angle = one.angle > angleMax ? angleMax : one.angle;
			one.angle = one.angle < angleMin ? angleMin : one.angle;
		}
	}
}

void Genetic::selection()
{
	unsigned int half = pupulationSize / 2;
	for (int i = 0; i < half; i++) {
		if (population[i].evaluation < population[i + half].evaluation) {
			population[i].offsetX = population[i + half].offsetX;
			population[i].offsetY = population[i + half].offsetY;
			population[i].angle = population[i + half].angle;
			population[i].scale = population[i + half].scale;
			population[i].evaluation = population[i + half].evaluation;
		}
	}
	genom bufor;
	int a, b;
	for (unsigned int i = 0; i < pupulationSize / 5; i++) {
		a = rand() % (pupulationSize / 2);
		b = rand() % (pupulationSize / 2);
		if (a != b) {
			memcpy(&bufor, &population[a], sizeof(genom));
			memcpy(&population[a], &population[b], sizeof(genom));
			memcpy(&population[b], &bufor, sizeof(genom));
		}
	}
}

void Genetic::cross()
{
	unsigned int half = pupulationSize / 2;
	unsigned int toggle;
	for (unsigned int i = 0; i < half; i += 2) {
		toggle = (rand() % 2 == 0 ? 1 : 0);
		population[i * 2].scale = population[i + toggle].scale;
		toggle = toggle == 0 ? 0 : 1;
		population[i * 2 + 1].scale = population[i + toggle].scale;

		toggle = (rand() % 2 == 0 ? 1 : 0);
		population[i * 2].offsetX = population[i + toggle].offsetX;
		toggle = toggle == 0 ? 0 : 1;
		population[i * 2 + 1].offsetX = population[i + toggle].offsetX;

		toggle = (rand() % 2 == 0 ? 1 : 0);
		population[i * 2].offsetY = population[i + toggle].offsetY;
		toggle = toggle == 0 ? 0 : 1;
		population[i * 2 + 1].offsetY = population[i + toggle].offsetY;

		toggle = (rand() % 2 == 0 ? 1 : 0);
		population[i * 2].angle = population[i + toggle].angle;
		toggle = toggle == 0 ? 0 : 1;
		population[i * 2 + 1].angle = population[i + toggle].angle;
	}
}

void Genetic::crossV2() {
	unsigned int half = pupulationSize / 2;
	unsigned int toggle;
	for (unsigned int i = 0; i < half; i += 2) {
		toggle = (rand() % 2 == 0 ? 0 : 1);
		population[i * 2].scale = population[i + toggle].scale;
		population[i * 2 + 1].scale = (population[i].scale + population[i + 1].scale) / 2;

		toggle = (rand() % 2 == 0 ? 0 : 1);
		population[i * 2].offsetX = population[i + toggle].offsetX;
		population[i * 2 + 1].offsetX = (population[i].offsetX + population[i + 1].offsetX) / 2;

		toggle = (rand() % 2 == 0 ? 0 : 1);
		population[i * 2].offsetY = population[i + toggle].offsetY;
		population[i * 2 + 1].offsetY = (population[i].offsetY + population[i + 1].offsetY) / 2;

		toggle = (rand() % 2 == 0 ? 0 : 1);
		population[i * 2].angle = population[i + toggle].angle;
		population[i * 2 + 1].angle = (population[i].angle + population[i + 1].angle) / 2;
	}
}

void Genetic::displayBest()
{
	vec2 translation = { best.offsetX, best.offsetY };
	Mat dst(basicImage);
	dst = scaleImg(dst, best.scale);
	dst = rotateImgR(dst, detectLocation(dst), best.angle);
	translateImg(dst, translation);
	std::cout << "DOPASOWANIE:   " << znajdzDopasownaie(dst, toCompare) << std::endl;
	std::cout << "SCALE:         " << best.scale << std::endl;
	std::cout << "OFFSET:        " << best.offsetX << " , " << best.offsetY << std::endl;
	std::cout << "ANGLE:         " << best.angle << std::endl;
	cv::Mat kolorowany = cv::Mat::zeros(basicImage.rows, basicImage.cols, CV_8UC3);
	rozniceKolorowany(toCompare, dst, kolorowany);
}

Genetic::Genetic(Mat basicImg, Mat toCompareImg) :
	basicImage(basicImg),
	toCompare(toCompareImg)
{
	srand(time(NULL));
	initPopulation();
}

void Genetic::initPopulation() {
	for (auto & i : population) {
		float r = (float)rand() / (float)RAND_MAX;
		i.scale = scaleMin + (scaleMax - scaleMin) * r;
		r = (float)rand() / (float)RAND_MAX;
		i.offsetX = (int)(offsetMin + (offsetMax - offsetMin) * r);
		r = (float)rand() / (float)RAND_MAX;
		i.offsetY = (int)(offsetMin + (offsetMax - offsetMin) * r);
		r = (float)rand() / (float)RAND_MAX;
		i.angle = angleMin + (angleMax - angleMin) * r;
	}
}

void Genetic::mainLoop()
{
	for (unsigned int i = 0; i < iterations; i++) {
		std::cout << "iteracja:   " << i << std::endl;
		memcpy(&population[0], &best, sizeof(best));
		if (actual - history[i % 20] < 0.01 && best.evaluation < 0.95 && i > 19) {
			for (auto o : history) o = 0;
			initPopulation();
			i = 0;
			best.evaluation = -1.0;
		}
		selection();
		crossV2();
		mutate();
		evaluate(i);
		displayBest();
		cvWaitKey(1);
	}
}


Genetic::~Genetic()
{
}
