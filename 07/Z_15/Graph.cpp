#include "Graph.h"

WeightEdge::WeightEdge():
	first(0),
	second(0),
	weight(0)
{
}

WeightEdge::WeightEdge(
	const size_t& _first, 
	const size_t& _second, 
	const double& _weight) :
	first(_first),
	second(_second),
	weight(_weight)
{
}

WeightEdge::~WeightEdge()
{
}

std::ostream& operator<<(std::ostream& out, const WeightEdge& edge)
{
	out << edge.first << ' ' << edge.second << ' ' << edge.weight << '\n';
	return out;
}

bool WeightEdge::operator<(const WeightEdge& second) const noexcept
{
	double eps = 0.000001;
	return weight - second.weight < eps;
}