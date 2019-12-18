#pragma once
#include <vector>
#include <ctime>
#include "Graph.h"

class Generator
{
public:
	std::vector<WeightEdge> GenEdge(const std::vector<Point>& points);
	std::vector<Point> operator()(const size_t& N);
private:
	double frand(double fMin = -0.7, double fMax = 0.7);
	Point normalRand();
	double dst(const Point& a, const Point& b);
};