#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::min;

vector<size_t> ZFunc(const string& s)
{
	size_t n = s.size();
	vector<size_t> z(n);
	for (size_t i = 1, l = 0, r = 0; i < n; ++i)
	{
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
		{
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

int main()
{
	string s;
	std::cin >> s;
	size_t p = s.size();
	s += "$";
	{
		string text;
		std::cin >> text;
		s += text;
	}
	auto res = ZFunc(s);
	for (size_t i = p + 1; i < res.size(); ++i)
		if(res[i] == p)
			std::cout << i - p - 1 << ' ';
	return 0;
}
