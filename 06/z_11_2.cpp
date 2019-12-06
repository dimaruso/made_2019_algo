#include <iostream>
#include <vector>
#include <list>
#include <queue>
using std::vector;
using std::list;
using std::queue;

class MyGraf
{
public:
	MyGraf(const size_t& _V, const size_t& _E);
	~MyGraf();
	size_t PathCount(const size_t& _u, const size_t& _v);
private:
	size_t E, V;
	vector<list<size_t>> G;
};

MyGraf::MyGraf(const size_t& _V, const size_t& _E):
	V(_V),
	E(_E),
	G(_V)
{
	size_t a, b;
	for (size_t i = 0; i < E; ++i)
	{
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
}

MyGraf::~MyGraf()
{
	V = 0;
	E = 0;
	G.clear();
	G.shrink_to_fit();
}

size_t MyGraf::PathCount(const size_t& a, const size_t& b)
{
	vector<size_t> visited(V, -1);
	vector<size_t> pat(V,1);

	size_t CountPath = 0;
	size_t maxLen = -1;
	queue<size_t> q;

	q.push(a);
	visited[a] = 0;
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		for (auto to : G[cur])
		{
			if (visited[to] > visited[cur] && maxLen > visited[cur])
			{
				if (visited[to] == visited[cur] + 1)
				{
					pat[to] += pat[cur];
				}
				else if (to != b)
				{
					visited[to] = visited[cur]+1;
					pat[to] = pat[cur];
					q.push(to);
				}
				else
				{
					maxLen = visited[cur] + 1;
					CountPath +=pat[cur];
				}
			}
		}
	}
	return CountPath;
}

int main()
{
	size_t V, E;
	size_t a, b;
	std::cin >> V >> E;
	MyGraf G(V,E);
	std::cin >> a >> b;
	size_t res = G.PathCount(a,b);
	std::cout << res;
	return 0;
}
