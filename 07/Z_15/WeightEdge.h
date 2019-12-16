#pragma once
#include <ostream>

class WeightEdge
{
public:
	WeightEdge();
	WeightEdge(
		const size_t& _first, 
		const size_t& _second, 
		const double& _weight);
	~WeightEdge();

	friend std::ostream& operator<<(std::ostream& out, const WeightEdge& edge);

	bool operator<(const WeightEdge& second) const noexcept;

	size_t first;
	size_t second;
	double weight;
};

class Point
{
public:
	Point() : X(0), Y(0) {}
	Point(const double& _X, const double& _Y): X(_X), Y(_Y) {}
	~Point() {}

	friend std::ostream& operator<<(std::ostream& out, const Point& point)
	{
		out << point.X << ' ' << point.Y << '\n';
	}

	double X;
	double Y;
};