#include "Metrics.h"
#include <algorithm>

double Mean::operator()(const std::vector<double>& X)
{
	double res = 0;

	for (auto& i : X)
		res += i;

	res /= X.size();
	return res;
}

double StandardDeviation::operator()(const std::vector<double>& X)
{
	double res = 0;
	Mean mean;
	auto m = mean(X);

	for (auto& i : X)
		res += (i - m)*(i - m);

	res = sqrt(res/X.size());
	return res;
}