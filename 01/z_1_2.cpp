#include <iostream>
#include <cstring>
#include <cassert>

class MyNotList
{

public:
	MyNotList();
	~MyNotList();
	void push_back(int data);
	void push_front(int data);
	int pop_back();
	int pop_front();
	void prin();
	bool is_empty();
private:	
	int* dataset;
	int size;
	int len;
	int head;
	int tail;
protected:
	void upData();
};
	void MyNotList::prin() {
		
		for (int i = 0; i < len; i++)
			std::cout << dataset[i] << " ";
		std::cout << std::endl;
	};
	MyNotList::MyNotList() :
		head(0),
		tail(0),
		dataset(new int[8]),
		size(0),
		len(8)
	{
	}
	MyNotList::~MyNotList()
	{
		delete[] dataset;
	}
	void MyNotList::upData()
	{
		int newLen = len * 2;
		int *newDataset = new int[newLen];
		if (head < tail) {
			memcpy(newDataset, dataset, size*sizeof(int));
		}
		else {
			memcpy(newDataset+size-head, dataset, (tail + 1)*sizeof(int));
			memcpy(newDataset, dataset+head, (size - head) * sizeof(int));
			head = 0;
			tail = size - 1;
		}
		delete[] dataset;
		dataset = newDataset;
		len = newLen;
	}
	int MyNotList::pop_front()
	{
		assert(size > 0);
		if (size == 1)
		{
			size--;
			return dataset[tail];
		}
		else
		{
			int value = dataset[head];
			if (head == len - 1) head = 0;
			else head++;
			size--;
			return value;
		}
	}
	void MyNotList::push_back(int data)
	{
		if (size == len) upData();

		if (size == 0) {
			dataset[tail] = data;
			size++;
		}
		else
		{
			if (tail == len -1)	tail = 0;
			else tail++;

			size++;
			dataset[tail] = data;
		}
		
	}
	void MyNotList::push_front(int data)
	{
		if (size == len) upData();

		if (size == 0) {
			
			dataset[head] = data;
			size++;
		}
		else
		{
			if (head == 0) head = len - 1;
			else head--;
			dataset[head] = data;
			size++;
		}
	}
	int MyNotList::pop_back()
	{
		assert(size > 0);
		if (size == 1)
		{
			size--;
			return dataset[tail];
		}
		else 
		{
			int value = dataset[tail];

			if (tail == 0)	tail = len - 1;
			else tail--;
			size--;
			return value;
		}
	}
	bool MyNotList::is_empty()
	{
		return !size;
	}
int main() {

	MyNotList q;
	int n;
	int com;
	int value;
	int res = 1;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cin >> com >> value;
		if (res)
		switch (com)
		{
		case 1:
			q.push_front(value);
			break;
		case 2:
			if (q.is_empty())
			{
				if (value != -1) res = 0;
			} else
			if (q.pop_front() != value) res = 0;
			break;
		case 3:
			q.push_back(value);
			break;
		case 4:
			if (q.is_empty())
			{
				if (value != -1) res = 0;
			}
			else
			if (q.pop_back() != value) res = 0;
			break;
		default:
			break;
		}
	}
	if (res) 
		std::cout << "YES" << std::endl;
	else 
		std::cout << "NO" << std::endl;
	//q.~MyNotList();
	//system("pause");
	return 0;
}
