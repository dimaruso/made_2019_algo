#include <iostream>
class MinHeap
{
public:
	MinHeap(int _l);
	~MinHeap();	
	int TakeMin();
	void Add(int element);
	int len();
private:
	int* arr;
	int l;
	void SiftUp(int i);
	void SiftDown(int i);
	void BuildHeap();
};

MinHeap::MinHeap(int _l):
	l(_l),
	arr(new int[_l])
{
	for (int i = 0; i < l; i++)
	{
		std::cin >> arr[i];
	}
	BuildHeap();
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

int MinHeap::len()
{
	return l;
}

void MinHeap::Add(int element) {
	arr[l] = element;
	l++;
	SiftUp(l-1);
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

	int sum = 0;
	if(n>1)
		for (int t; a.len() > 1;)
		{
			t = a.TakeMin()+a.TakeMin();
			sum += t;
			if(a.len() > 0) a.Add(t);
		}
	std::cout << sum << std::endl;
	//a.~MinHeap();
	//system("pause");
	return 0;
}
