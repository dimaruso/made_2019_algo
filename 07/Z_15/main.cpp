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

	//Number of vertices
	size_t N = _N;

	//Sample size
	size_t K = 10;

	//Sample MST
	std::vector<double> mst;
	mst.reserve(K);
	
	//Sample true solution
	std::vector<double> truePath;
	truePath.reserve(K);

	//Sample quality approach = true solution / (2 * MST)
	std::vector<double> quality;
	quality.reserve(K);

	for (size_t i = 0; i < K; ++i)
	{
		auto points = gen(N);
		auto edges = gen.GenEdge(points);

		mst.push_back(MST(N, edges));
		truePath.push_back(TruePath(points));

		quality.push_back(truePath[i]/(2*mst[i]));
	}
	
	out << "N = " << N << '\n';
	out << "Mean 2*MST = " << 2*mean(mst) << '\n';
	out << "Mean true solution = " << mean(truePath) << '\n';
	out << "Mean quality approach = " << mean(quality) << '\n';
	out << "Standard Deviation quality approach = " << standardDeviation(quality) << '\n';
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