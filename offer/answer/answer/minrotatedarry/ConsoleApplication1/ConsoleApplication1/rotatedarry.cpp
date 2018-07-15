#include<iostream>
using namespace std;
int find(int arry[],int nlength)
{
	if (arry == NULL || nlength <= 0)
		throw new exception("error");
	int index1 = 0;
	int index2 = nlength - 1;
	int middle = 0;
	while (arry[index1] >= arry[index2])
	{
		if (index2 - index1 == 1)
		{
			middle = index2;
			break;
		}
		middle = (index1 + index2) / 2;
		if (arry[index1] == arry[index2] && arry[index1] == arry[middle])
		{
			int min = arry[index1];
			for (int i = index1+1; i <= index2; i++)
			{
				if (arry[i] < min)
				{
					min = arry[i];
				}
			}
			return min;
		}
		if (arry[index1] < arry[middle])
			index1 = middle;
		else if (arry[index2] > arry[middle])
			index2 = middle;
	}
	return arry[middle];
}
void main()
{	
	int a[] = { 1};
	try {
		cout << find(a, 5) << endl;
	}
	catch (exception*e)
	{
		cout << e->what() << endl;
	}
}