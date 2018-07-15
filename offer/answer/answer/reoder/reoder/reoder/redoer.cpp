#include<iostream>
void reoder(int* array)
{
	int p1 = 0;
	int p2 = 4;
	while (p1<p2)
	{ 
		if ((array[p1]) % 2 == 1)
			p1++;
		if ((array[p2]) % 2 == 0)
			p2--;
		if (array[p1] % 2 == 0 && array[p2] % 2 == 1&&p1<p2) 
		{
			int temp = array[p1];
			array[p1] = array[p2];
			array[p2] = temp;
		}
	}
}
int main()
{
	int a[] = { 1,2,3,4,5 };
	reoder(a);
}