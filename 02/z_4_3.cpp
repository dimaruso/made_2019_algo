#include <iostream>
#include <ctime>

template<class T>
class IsLessDefaultFunctor {
public:
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T, class IsLess = IsLessDefaultFunctor<T> >
int Partition(T* a, int n, IsLess isLess = IsLess()) {
	if (n <= 1) {
		return 0;
	}

	//take random element
	const int i_s = rand() % n;
	const T s = a[i_s];
	std::swap(a[i_s], a[n - 1]);

	//direct pass i, j
	int i = 0;
	int j = 0;
	while (j < n-1) {
		for (; j < n-2 && !isLess(a[j], s); ++j) {}
		if (isLess(a[j], s)) {
			std::swap(a[i++], a[j++]);
		}
		else if (j == n - 2) j = n;
	}
	std::swap(a[i], a[n - 1]);

	return i;
}

template<class T, class IsLess = IsLessDefaultFunctor<T> >
void QuickSort(T* a, int n, IsLess isLess = IsLess()) {
	int part = Partition(a, n, isLess);
	if (part > 0) QuickSort(a, part, isLess);
	if (part + 1 < n) QuickSort(a + part + 1, n-(part + 1), isLess);
}

template<class T, class IsLess = IsLessDefaultFunctor<T> >
void QuickFind(T* a, int n, int k, IsLess isLess = IsLess()) {
	int part = Partition(a, n, isLess);

	//non-recursive implementation
	int l = 0;
	int r = n;
	while (part != k)
	{	
		if (isLess(k, part))//(part > k)
		{
			r = part;
		
			part = Partition(a+l, r, isLess);
		}
		else if (isLess(part, k))//(part < k)
		{
			k -= part + 1;
			l += part + 1;
			r -= part + 1;

			part = Partition(a+l, r, isLess);
		}
	}
}

int main()
{
	srand(time(0));
	int n;
	int k;
	std::cin >> n >> k;
	int* a = new int[n];
	
	for (int i = 0; i < n; i++)
		std::cin >> a[i];

	QuickFind(a, n, k);

	
	if (n>0 && k < n)
		std::cout << a[k];

	delete[] a;
	//system("pause");
	return 0;
}
