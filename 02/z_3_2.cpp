#include <iostream>
#include <cstring>

template<class T>
class IsLessDefaultFunctor {
public:
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T, class IsLess = IsLessDefaultFunctor<T> >
void Merge(T* a, int la, T* b, int lb, IsLess isLess = IsLess())
{
	int i = 0;
	int j = 0;
	int lc = 0;
	T* c = new T[la+lb];

	while (i<la && j<lb)

		//if (a[i] <= b[j])
		if (isLess(a[i], b[j]))
		{
			c[lc] = a[i];
			lc++;
			i++;
		} 
		else
		{
			c[lc] = b[j];
			lc++;
			j++;
		}

	for (; i < la; i++)
	{
		c[lc] = a[i];
		lc++;
	}
	for (; j < lb; j++)
	{
		c[lc] = b[j];
		lc++;
	}

	memcpy(a, c, sizeof(T)*(lc));
	delete[] c;
}

template<class T, class IsLess = IsLessDefaultFunctor<T> >
void MergeSort(T* a, int l, IsLess isLess = IsLess())
{
	if (l<=1) return;

	int firstLen = l/2;
	int secondLen = l-firstLen;

	MergeSort(a, firstLen, isLess);
	MergeSort(a + firstLen, secondLen,isLess);

	//int* c = new int[l];
	Merge(a, firstLen, a + firstLen, secondLen,isLess);
	//delete[] c;
}

int main()
{
	int n;
	int k;
	std::cin >> n >> k;

	int* a = new int[n];

	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	//true solve
	if (n > 1 && k > 0)
	{
		MergeSort(a, (k < n) ? k : n);

		for (int t = 0, i = k, j = ((k * 2 < n) ? k * 2 : n); t == 0; i += k)
		{
			MergeSort(a + i , j - i);
			Merge(a + i-k, k, a + i , j - i);

			if (j >= n) t = 1;
			j += k;
			if (j > n) j = n;
		}
	}

	for (int i = 0; i < n; ++i)
		std::cout << a[i]  << " ";

	delete[] a;
	//system("pause");
	return 0;
}
