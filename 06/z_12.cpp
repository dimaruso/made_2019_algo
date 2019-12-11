#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <fstream>

using std::vector;
using std::list;
using std::set;

class MyGraf
{
public:
	MyGraf(const size_t& _V, const size_t& _E, std::ifstream& _in);
	~MyGraf();
	void find_bridges(void(*TakeBridge)(const vector<size_t>& res));	
private:
	struct V_Num
	{
		size_t nextv;
		size_t num;
		V_Num(size_t _nextv = 0, size_t _num = 0) :
			nextv(_nextv),
			num(_num)
		{}
	};
	size_t E, V;
	vector<list<V_Num>> G;
	size_t timer;
	vector<bool> visited;
	vector<size_t> timeIN;
	vector<size_t> timeRIN;
	vector<size_t> NumOfE;
	void DFS(V_Num v, int p = -1);
};

MyGraf::MyGraf(const size_t& _V, const size_t& _E, std::ifstream& _in) :
	V(_V+1),
	E(_E),
	G(_V+1)
{
	size_t a, b;
	for (size_t i = 1; i <= E; ++i)
	{
		_in >> a >> b;
		G[a].push_back(V_Num(b,i));
		G[b].push_back(V_Num(a,i));
	}
}

MyGraf::~MyGraf()
{
	V = 0;
	E = 0;
	G.clear();
	G.shrink_to_fit();
}

void  MyGraf::DFS(V_Num v, int p)
{
	visited[v.nextv] = true;
	timeIN[v.nextv] = timeRIN[v.nextv] = timer++;
	for(auto to: G[v.nextv])
	{
		if (to.nextv == p && to.num == v.num)  
			continue;
		if (visited[to.nextv])
			timeRIN[v.nextv] = std::min(timeRIN[v.nextv], timeIN[to.nextv]);
		else
		{
			DFS(to, v.nextv);
			timeRIN[v.nextv] = std::min(timeRIN[v.nextv], timeRIN[to.nextv]);
			if (timeRIN[to.nextv] > timeIN[v.nextv] )
				NumOfE.push_back(to.num);
		}
	}
}

void  MyGraf::find_bridges(void(*TakeBridge)(const vector<size_t>& res))
{
	timer = 0;
	visited.assign(V, false);
	timeIN.resize(V);
	timeRIN.resize(V);
	for (size_t i = 1; i < V; ++i)
		if (!visited[i])
			DFS(V_Num(i));

	std::sort(NumOfE.begin(), NumOfE.end());
	TakeBridge(NumOfE);

	timeIN.shrink_to_fit();
	timeRIN.shrink_to_fit();
	NumOfE.shrink_to_fit();
	visited.shrink_to_fit();
}

void printNumOfBridge(const vector<size_t>& res)
{
	std::ofstream out;
	out.open("bridges.out");

	out << res.size() << '\n';
	for (auto i : res)
		out << i << ' ';
}

void createFile()
{
	std::ofstream out;
	out.open("bridges.in");
	vector<size_t> inp{ 
		6, 7,
		1, 2,
		2, 3,
		3, 4,
		1, 3,
		4, 5,
		4, 6,
		4, 6 };
	for (auto i : inp)
		out << i << ' ';
}
int main()
{
	//createFile();
	std::ifstream in("bridges.in");
	size_t V, E;
	in >> V >> E;
	MyGraf G(V, E, in);
	G.find_bridges(printNumOfBridge);
	return 0;
}
