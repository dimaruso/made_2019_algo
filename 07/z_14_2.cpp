#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct EdgeWeight
{
	size_t a;
	size_t b;
	size_t weight;
	EdgeWeight(size_t _a = 0, size_t _b = 0, size_t _weight = 0) :
		a(_a),
		b(_b),
		weight(_weight)
	{}
	bool operator<(const EdgeWeight& second) const
	{
		return weight < second.weight;
	}
};

class DSU {
public:
	DSU(size_t count);

	size_t FindParent(size_t v);
	void Union(size_t v1, size_t v2);

private:
	vector<size_t> parent;
	vector<size_t> rank;
};

DSU::DSU(size_t count) :
	parent(count),
	rank(count, 0)
{
	for (size_t i = 0; i < count; ++i)
		parent[i] = i;
}

size_t DSU::FindParent(size_t v)
{
	if (v == parent[v])
		return v;
	parent[v] = FindParent(parent[v]);
	return parent[v];
}

void DSU::Union(size_t v1, size_t v2)
{
	size_t p1 = FindParent(v1);
	size_t p2 = FindParent(v2);
	if (p1 == p2)
		return;

	if (rank[p1] < rank[p2])
		parent[p1] = p2;
	else {
		parent[p2] = p1;
		if (rank[p1] == rank[p2])
			++rank[p1];
	}
}

size_t CruscalWeight(const size_t& V, vector<EdgeWeight>& G)
{
	size_t res = 0;
	std::sort(G.begin(), G.end());
	DSU solver(V+1);

	for (auto& E : G)
	{
		if (solver.FindParent(E.a) != solver.FindParent(E.b))
		{
			res += E.weight;
			solver.Union(E.a, E.b);
		}
	}
	return res;
}

int main()
{
	size_t V, E;
	std::cin >> V >> E;
	vector<EdgeWeight> G;
	G.reserve(E);
	size_t a, b, w;
	for (size_t i = 0; i < E; ++i)
	{
		std::cin >> a >> b >> w;
		G.push_back(EdgeWeight(a, b, w));
	}
	std::cout << CruscalWeight(V, G);
	return 0;
}
