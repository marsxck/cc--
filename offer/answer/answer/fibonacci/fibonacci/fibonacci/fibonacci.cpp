#include<iostream>
using namespace std;
int fibonacci(int n)
{
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return fibonacci(n-1) + fibonacci(n - 2);
}
int Fibonacci(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	int a1 = 0;
	int a2 = 1;
	int a3 = 1;  
	for (int i=2;i<=n;i++)
	{
		a3 = a1 + a2;
		a1 = a2;
		a2 = a3;
	}     
	return a3;
} 
void main()
{
	cout << fibonacci(20) << " " << Fibonacci(20) << endl;
}