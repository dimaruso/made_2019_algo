#include <iostream>
#include <ctime>

int Partition(int* a, int n) {
	if (n <= 1) {
		return 0;
	}

	//take random element
	const int i_s = rand() % n;
	const int s = a[i_s];
	std::swap(a[i_s], a[n - 1]);

	//direct pass i, j
	int i = 0;
	int j = 0;
	while (j < n-1) {
		for (; j < n-2 && a[j] >= s; ++j) {}
		if (a[j] < s) {
			std::swap(a[i++], a[j++]);
		}
		else if (j == n - 2) j = n;
	}
	std::swap(a[i], a[n - 1]);

	return i;
}
void QuickSort(int* a, int n) {
	int part = Partition(a, n);
	if (part > 0) QuickSort(a, part);
	if (part + 1 < n) QuickSort(a + part + 1, n-(part + 1));
}

void QuickFind(int* a, int n, int k) {
	int part = Partition(a, n);

	//non-recursive implementation
	int l = 0;
	int r = n;
	while (part != k)
	{
		if (part > k)
		{
			r = part;
		
			part = Partition(a+l, r);
		}
		else if (part < k)
		{
			k -= part + 1;
			l += part + 1;
			r -= part + 1;

			part = Partition(a+l, r);
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

	QuickFind(a,n,k);

	
	if (n>0 && k <= n)
	std::cout << a[k];

	delete[] a;
	//system("pause");
	return 0;
}
