#include<iostream>
using namespace std;
void sort(int a[],int nlength)
{
	if (a == NULL || nlength <= 0)
		return;
	int count[100];
	for (int i = 0; i < 100; i++)
		count[i] = 0;
	for (int j = 0; j < nlength; j++)
		count[a[j]]++;
	int index = 0;
	for (int k = 0; k < 100; k++)
	{
		for (int i = 0; i < count[k]; i++)
		{
			a[index] = k;
			index++;
		}
	}

}
void main()
{
	int a[] = { 34,22,11,23,45 };
	sort(a, 5);
}