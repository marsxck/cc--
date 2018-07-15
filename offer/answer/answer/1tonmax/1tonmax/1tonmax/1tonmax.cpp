#include<iostream>
using namespace std;
void core(char* num, int length, int index)
{
	if (index == length - 1)
	{
		cout << num << endl;
		return;
	}
	for (int i = 0; i < 10; i++)
	{
		num[index + 1] = '0' + i;
		core(num, length, index + 1);
	}
}
void PrintNMax(int n)
{
	if (n <= 0)
		return;
	char* num = new char[n + 1];
	num[n] = '\0';
	for (int i=0;i<10;i++)
	{
		num[0] = i + '0';
		core(num,n,0);
	}
	delete[]num;
}
void print2(int n)
{
	if (n <= 0)
		return;
	char* num = new char[n + 1];
	num[n] = '\0';
	for (int i = 0; i < n; i++)
		num[i] = '0';
	int sum = 0,nTake=0;
	while (1)
	{
		for (int i = n - 1; i >= 0; i--)
		{
			sum = num[i] - '0' + nTake;
			if (i == n - 1)
				sum++;
			if (sum >= 10)
			{
				//½øÎ»
				if (i == 0)
					return;
				else
				{
					nTake = 1;
					sum -= 10;
					num[i] = sum + '0';
					cout << num << endl;
				}
			}
			else
			{
				num[i] = sum + '0';
				cout << num << endl;
				break;
			}
		}
	}
}
void main()
{
	PrintNMax(1);
	print2(1);
}