#pragma once
#include <vector>

class Mean
{
public:
	double operator()(const std::vector<double>& X);
};

class StandardDeviation
{
public:
	double operator()(const std::vector<double>& X);
};