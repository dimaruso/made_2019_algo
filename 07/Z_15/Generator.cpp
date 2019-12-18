#include <algorithm>
#include <cassert>
#include "Generator.h"

std::vector<WeightEdge> Generator::GenEdge(const std::vector<Point>& points)
{
	size_t N = points.size();
	std::vector<WeightEdge> G;
	G.reserve(N*(N-1)/2);
	for (size_t i = 0; i < N; ++i)
		for (size_t j = i+1; j < N; ++j)
		G.push_back(WeightEdge(i,j,dst(points[i],points[j])));
	return G;
}

std::vector<Point> Generator::operator()(const size_t& N)
{
	std::vector<Point> Points;
	Points.reserve(N);
	for (size_t i = 0; i < N; ++i)
		Points.push_back(normalRand());
	return Points;
}

double Generator::frand(double fMin, double fMax)
{
	double f = fMin + (fMax - fMin) * (rand() % RAND_MAX) / RAND_MAX;
	return f;
}

Point Generator::normalRand()
{
	double u = frand();
	double v = frand();
	double s = u * u + v * v;
	assert(s < 1);
	double x = u * sqrt(-2 * log(s) / s);
	double y = v * sqrt(-2 * log(s) / s);
	return Point(x, y);
}

double Generator::dst(const Point& a, const Point& b)
{
	return sqrt((a.X - b.X)*(a.X - b.X) + (a.Y - b.Y)*(a.Y - b.Y));
}