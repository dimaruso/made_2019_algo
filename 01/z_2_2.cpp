#include <iostream>

//for min heap
void SiftUp(int* arr, int l, int i) {
	int j = i;
	while (j > 0 && arr[j] < arr[(j - 1) / 2])
	{
		std::swap(arr[j], arr[(j - 1) / 2]);
		j = (j - 1) / 2;
	}
}

//for max heap
void SiftDown(int* arr, int l, int i) {
	int j = i;
	int t = 1;
	while (2*j+1 < l && t )
	{
		if (2 * j + 2 == l)
		{
			if (arr[j] > arr[2 * j + 1])
			{
				std::swap(arr[j], arr[2 * j + 1]);
				j = 2 * j + 1;
			} else
				t = 0;
		} else
		if (arr[j] > arr[2 * j + 1] && arr[2 * j + 1] <= arr[2 * j + 2])
		{
			std::swap(arr[j], arr[2 * j + 1]);
			j = 2 * j + 1;
		} else
			if (arr[j] > arr[2 * j + 2] && arr[2 * j + 1] >= arr[2 * j + 2])
			{
				std::swap(arr[j], arr[2 * j + 2]);
				j = 2 * j + 2;
			}
			else
				t = 0;
	}
}
//for min heap
void SiftDownmin(int* arr, int l, int i) {
	int j = i;
	int t = 1;
	while (2 * j + 1 < l && t)
	{
		if (2 * j + 2 == l)
		{
			if (arr[j] > arr[2 * j + 1])
			{
				std::swap(arr[j], arr[2 * j + 1]);
				j = 2 * j + 1;
			}
			else
				t = 0;
		}
		else
			if (arr[j] > arr[2 * j + 1] && arr[2 * j + 1] <= arr[2 * j + 2])
			{
				std::swap(arr[j], arr[2 * j + 1]);
				j = 2 * j + 1;
			}
			else
				if (arr[j] > arr[2 * j + 2] && arr[2 * j + 1] >= arr[2 * j + 2])
				{
					std::swap(arr[j], arr[2 * j + 2]);
					j = 2 * j + 2;
				}
				else
					t = 0;
	}
}

void BuildHeap(int* arr, int l) {
	for (int i = (l/2-1); i >= 0; --i) {
		SiftDownmin(arr, l, i);
	}
}

void Add(int* arr, int& l, int element) {
	arr[l] = element;
	l++;
	SiftUp(arr, l, l-1);
}

void HeapSort(int* a, int n) {
	int heapSize = n;
	BuildHeap(a, heapSize);
	while (heapSize > 1) {
		std::swap(a[0], a[heapSize - 1]);
		--heapSize;
		SiftDownmin(a, heapSize, 0);
	}
}

int TakeMin(int* a, int& l) {
	if (l < 1)
	{
		l--;
		return 0;
	}
	else
	{
		int min = a[0];
		std::swap(a[0], a[l - 1]);
		l--;

		SiftDownmin(a, l, 0);

		return min;
	}
}

int main()
{
	int n;
	std::cin >> n;

	int* a = new int[n];
	for (int i = 0; i < n; i++)
		std::cin >> a[i];

	BuildHeap(a, n);
	//HeapSort(a, n);
	
	int sum = 0;
	int t;
	if(n>1)
		for (; n > 1;)
		{
			t = TakeMin(a, n)+TakeMin(a, n);
			sum += t;
			if(n > 0) Add(a, n, t);
		}
	std::cout << sum << std::endl;
	//system("pause");
	return 0;
}
