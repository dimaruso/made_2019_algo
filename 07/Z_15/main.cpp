#include <iostream>
#include <fstream>
#include "Generator.h"
#include "Cruscal.h"
#include "Metrics.h"

void test(const size_t& _N, std::ofstream& out)
{
	//Graph generator
	Generator gen;

	//Cruskal Algorithm
	Cruscal MST;

	//Brood Force Algorithm
	BroodForce TruePath;

	//Mean
	Mean mean;

	//Standard Deviation
	StandardDeviation  standardDeviation;

	//number of vertices
	size_t N = _N;

	//number of iterations
	size_t K = 10;

	//Sample Weights
	std::vector<double> res;
	res.reserve(K);

	for (size_t i = 0; i < K; ++i)
	{
		auto points = gen(N);
		auto edges = gen.GenEdge(points);
		res.push_back(MST(N, edges) / TruePath(points));
	}

	out << "N = " << N << '\n';
	out << "Mean = " << mean(res) << '\n';
	out << "Standard Deviation = " << standardDeviation(res) << '\n';
	out << '\n';
}

int main()
{
	srand((unsigned)time(0));
	std::ofstream out;
	out.open("result.txt");
	for (size_t i = 2; i <= 10; ++i)
		test(i, out);
	return 0;
}