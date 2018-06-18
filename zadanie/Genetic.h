#pragma once
#include "stdafx.h"
#include <time.h>
#include <limits.h>
#include "algorithms.h"

typedef struct genom {
	int offsetX, offsetY;
	float scale;
	float angle;
	float evaluation;
};

class Genetic
{
public:
	const unsigned int pupulationSize = 20;
	const unsigned int iterations = 60;
	std::vector<genom> population = std::vector<genom>(pupulationSize);
	Mat basicImage;
	Mat toCompare;
	genom best;
	float history[20] = {20};
	float actual;
	float scaleMin = 0.7;
	float scaleMax = 0.99;
	int offsetMin = -100;
	int offsetMax = 100;
	float angleMin = -45.0f;
	float angleMax = 45.0f;
	
	void evaluate(unsigned int);
	void mutate();
	void selection();
	void cross();
	void crossV2();
	void displayBest();
	void mainLoop();
	void initPopulation();

	Genetic(Mat basicImage, Mat toCompare);
	~Genetic();
};

