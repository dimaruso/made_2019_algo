#pragma once
#include "DSU.h"
#include "WeightEdge.h"

class Cruscal
{
public:
	double operator()(const size_t& V, std::vector<WeightEdge>& G);
};

class BroodForce
{
public:
	double operator()(const std::vector<Point>& G);
private:
	double dst(const Point& a, const Point& b);
};