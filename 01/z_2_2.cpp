#include <iostream>
class MinHeap
{
public:
	MinHeap(int _l);
	~MinHeap();
	void SiftUp(int i);
	void SiftDown(int i);
	void BuildHeap();
	void HeapSort();
	int TakeMin();
	void Add(int element);
	int l;
private:
	int* arr;
};

MinHeap::MinHeap(int _l):
	l(0),
	arr(new int[_l])
{
}

MinHeap::~MinHeap()
{
	delete[] arr;
}

void MinHeap::SiftUp(int i) {
	int j = i;
	while (j > 0 && arr[j] < arr[(j - 1) / 2])
	{
		std::swap(arr[j], arr[(j - 1) / 2]);
		j = (j - 1) / 2;
	}
}

void MinHeap::SiftDown(int i) {
	int j = i;
	int t = 1;

	while (2 * j + 1 < l && t)
	{
//********************************************************
		//only one son
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
//********************************************************
		else
			//left son is smaller
			if (arr[j] > arr[2 * j + 1] && arr[2 * j + 1] <= arr[2 * j + 2])
			{
				std::swap(arr[j], arr[2 * j + 1]);
				j = 2 * j + 1;
			}
			else
				//right son is smaller
				if (arr[j] > arr[2 * j + 2] && arr[2 * j + 1] >= arr[2 * j + 2])
				{
					std::swap(arr[j], arr[2 * j + 2]);
					j = 2 * j + 2;
				}
				else
					t = 0;
	}
}

void MinHeap::BuildHeap() {
	for (int i = (l/2-1); i >= 0; --i) {
		SiftDown(i);
	}
}

void MinHeap::Add(int element) {
	arr[l] = element;
	l++;
	SiftUp(l-1);
}

void MinHeap::HeapSort() {
	int heapSize = l;
	BuildHeap();
	while (heapSize > 1) {
		std::swap(arr[0], arr[heapSize - 1]);
		--heapSize;
		SiftDown(0);
	}
}

int MinHeap::TakeMin() {
	if (l < 1)
	{
		l--;
		return 0;
	}
	else
	{
		int min = arr[0];
		std::swap(arr[0], arr[l - 1]);
		l--;
		SiftDown(0);
		return min;
	}
}

int main()
{
	int n;
	std::cin >> n;
	MinHeap a(n);

	int t;
	for (int i = 0; i < n; i++)
	{
		std::cin >> t;
		a.Add(t);
	}

	int sum = 0;
	if(n>1)
		for (;a.l > 1;)
		{
			t = a.TakeMin()+a.TakeMin();
			sum += t;
			if(a.l > 0) a.Add(t);
		}
	std::cout << sum << std::endl;
	//a.~MinHeap();
	//system("pause");
	return 0;
}
