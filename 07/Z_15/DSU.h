#pragma once
#include <vector>

class DSU
{
public:
	DSU(size_t count);

	size_t FindParent(size_t v);
	void Union(size_t v1, size_t v2);

private:
	std::vector<size_t> parent;
	std::vector<size_t> rank;
};