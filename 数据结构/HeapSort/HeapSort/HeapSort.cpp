#include<iostream>
void Adjust(int arr[],int nLength,int root)
{
	int min;
	for (min = 2 * root + 1; min <= nLength - 1; min = 2 * root + 1)
	{
		if (min + 1 <= nLength - 1)
		{
			if (arr[min] > arr[min + 1])
			{
				min = min + 1;
			}
		}
		if (arr[root] > arr[min])
		{
			arr[root] = arr[root] ^ arr[min];
			arr[min] = arr[root] ^ arr[min];
			arr[root] = arr[root] ^ arr[min];
			root = min;
		}
		else
		{
			break;
		}
	}

}
int *fun(int a)
{
	static int ret;
	ret = a;
	return &ret;
}
int main()
{
	int a[] = { 1,3,6,77,2 };
	int i;
	for (i = 0; i < 10; i++);
	int length = sizeof(a) / sizeof(a[0]);
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		Adjust(a,length,i);
	}
	for (int i = length - 1; i >= 1; i--)
	{
		a[0] = a[0] ^ a[i];
		a[i] = a[0] ^ a[i];
		a[0] = a[0] ^ a[i];
		Adjust(a, i, 0);
	}
	std::cout << *fun(2) - *fun(1);
 }