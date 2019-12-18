#include <algorithm>
#include <cassert>
#include "Cruscal.h"

double Cruscal::operator()(const size_t& V, std::vector<WeightEdge>& G)
{
	double res = 0;
	std::sort(G.begin(), G.end());
	DSU dsu(V);

	for (auto& E : G)
	{
		if (dsu.FindParent(E.first) != dsu.FindParent(E.second))
		{
			res += E.weight;
			dsu.Union(E.first, E.second);
		}
	}
	return res;
}

double BroodForce::operator()(const std::vector<Point>& G)
{
	double eps = 0.000001;
	double res = INFINITY;
	assert(G.size() < 11);
	assert(G.size() > 1);
	for (size_t i1 = 0; i1 < G.size(); ++i1)
	{
		double tmp = 0;
		std::vector<bool> visited(G.size(), false);
		visited[i1] = true;
		for (size_t i2 = 0; i2 < G.size(); ++i2)
		{
			if (visited[i2]) continue;
			visited[i2] = true;
			tmp += dst(G[i1],G[i2]);
			if (G.size() == 2) 
			{
				tmp += dst(G[i2], G[i1]);
				if (tmp - res < eps) res = tmp;
				tmp -= dst(G[i2], G[i1]);
			} else
			for (size_t i3 = 0; i3 < G.size(); ++i3)
			{
				if (visited[i3]) continue;
				visited[i3] = true;
				tmp += dst(G[i2], G[i3]);
				if (G.size() == 3)
				{
					tmp += dst(G[i3], G[i1]);
					if (tmp - res < eps) res = tmp;
					tmp -= dst(G[i3], G[i1]);
				} else
				for (size_t i4 = 0; i4 < G.size(); ++i4)
				{
					if (visited[i4]) continue;
					visited[i4] = true;
					tmp += dst(G[i3], G[i4]);
					if (G.size() == 4)
					{
						tmp += dst(G[i4], G[i1]);
						if (tmp - res < eps) res = tmp;
						tmp -= dst(G[i4], G[i1]);
					} else
					for (size_t i5 = 0; i5 < G.size(); ++i5)
					{
						if (visited[i5]) continue;
						visited[i5] = true;
						tmp += dst(G[i4], G[i5]);
						if (G.size() == 5)
						{
							tmp += dst(G[i5], G[i1]);
							if (tmp - res < eps) res = tmp;
							tmp -= dst(G[i5], G[i1]);
						} else
						for (size_t i6 = 0; i6 < G.size(); ++i6)
						{
							if (visited[i6]) continue;
							visited[i6] = true;
							tmp += dst(G[i5], G[i6]);
							if (G.size() == 6)
							{
								tmp += dst(G[i6], G[i1]);
								if (tmp - res < eps) res = tmp;
								tmp -= dst(G[i6], G[i1]);
							} else
							for (size_t i7 = 0; i7 < G.size(); ++i7)
							{
								if (visited[i7]) continue;
								visited[i7] = true;
								tmp += dst(G[i6], G[i7]);
								if (G.size() == 7)
								{
									tmp += dst(G[i7], G[i1]);
									if (tmp - res < eps) res = tmp;
									tmp -= dst(G[i7], G[i1]);
								} else
								for (size_t i8 = 0; i8 < G.size(); ++i8)
								{
									if (visited[i8]) continue;
									visited[i8] = true;
									tmp += dst(G[i7], G[i8]);
									if (G.size() == 8)
									{
										tmp += dst(G[i8], G[i1]);
										if (tmp - res < eps) res = tmp;
										tmp -= dst(G[i8], G[i1]);
									} else
									for (size_t i9 = 0; i9 < G.size(); ++i9)
									{
										if (visited[i9]) continue;
										visited[i9] = true;
										tmp += dst(G[i8], G[i9]);
										if (G.size() == 9)
										{
											tmp += dst(G[i9], G[i1]);
											if (tmp - res < eps) res = tmp;
											tmp -= dst(G[i9], G[i1]);
											
										}
										else
										for (size_t i10 = 0; i10 < G.size(); ++i10)
										{
											if (visited[i10]) continue;
											tmp += dst(G[i9], G[i10]);
											if (G.size() == 10)
											{
												tmp += dst(G[i10], G[i1]);
												if (tmp - res < eps) res = tmp;
												tmp -= dst(G[i10], G[i1]);
											}
											tmp -= dst(G[i9], G[i10]);
										}
										tmp -= dst(G[i8], G[i9]);
										visited[i9] = false;
									}
									tmp -= dst(G[i7], G[i8]);
									visited[i8] = false;
								}
								tmp -= dst(G[i6], G[i7]);
								visited[i7] = false;
							}
							tmp -= dst(G[i5], G[i6]);
							visited[i6] = false;
						}
						tmp -= dst(G[i4], G[i5]);
						visited[i5] = false;
					}
					tmp -= dst(G[i3], G[i4]);
					visited[i4] = false;
				}
				tmp -= dst(G[i2], G[i3]);
				visited[i3] = false;
			}
			tmp -= dst(G[i1], G[i2]);
			visited[i2] = false;
		}
	}
	return res;
}

double BroodForce::dst(const Point& a, const Point& b)
{
	return sqrt((a.X - b.X)*(a.X - b.X) + (a.Y - b.Y)*(a.Y - b.Y));
}