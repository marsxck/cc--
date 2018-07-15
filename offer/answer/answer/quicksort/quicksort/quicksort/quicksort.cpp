#include<iostream>
using namespace std;
int Partition(int a[], int nbegin, int nend)
{
	if (a == NULL || nbegin > nend || nbegin < 0 || nend < 0)
		return -1;
	int nSmall = nbegin - 1;
	int index = nbegin;
	for (index; index < nend; index++)
	{
		if (a[index] < a[nend])
		{
			nSmall++;
			if (nSmall != index)
			{
				a[nSmall] = a[nSmall] ^ a[index];
				a[index] = a[nSmall] ^ a[index];
				a[nSmall] = a[nSmall] ^ a[index];
			}
		}
	}
	nSmall++;
	if (nSmall != nend)
	{
		a[nSmall] = a[nSmall] ^ a[nend];
		a[nend] = a[nSmall] ^ a[nend];
		a[nSmall] = a[nSmall] ^ a[nend];
	}
	return nSmall;
}
void quicksort(int a[],int nbegin,int nend)
{
	if (a == NULL || nbegin >= nend || nbegin < 0 || nend <= 0)
		return;
	int index = Partition(a, nbegin, nend);
	if (index > nbegin)
		quicksort(a, nbegin, index - 1);
	if (index < nend)
		quicksort(a, index + 1, nend);
}
void main()
{
	int a[] = { 1,4,2,3,7,9,5 };
	quicksort(a, 0, 6);
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		cout << a[i] << " ";
	}

}