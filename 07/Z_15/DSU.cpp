#include "DSU.h"

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