#include <iostream>
#include <cstring>

void Merge(int* a, int la, int* b, int lb,int* c)
{
	int i = 0;
	int j = 0;
	int lc = 0;

	while (i<la && j<lb)

		if (a[i] <= b[j])
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
}

void MergeSort(int* a, int l)
{
	if (l<=1) return;

	int firstLen = l/2;
	int secondLen = l-firstLen;

	MergeSort(a, firstLen);
	MergeSort(a + firstLen, secondLen);

	int* c = new int[l];// *(l);
	Merge(a, firstLen, a + firstLen, secondLen,c);
	

	memcpy(a,c,sizeof(int)*(l));
	delete[] c;
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
	if (n>1 && k>0)
	for (int t = 0, i = 0, j = ((k * 2 <  n)? k*2: n) ; t == 0; i+=k)
	{
		MergeSort(a+i, j-i);
		if (j >= n) t = 1;
		j += k;
		if (j > n) j = n;

	}

	for (int i = 0; i < n; ++i)
		std::cout << a[i]  << " ";

	delete[] a;
	//system("pause");
	return 0;
}
