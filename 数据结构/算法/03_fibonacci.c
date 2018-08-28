#include<stdio.h>

int Fibonacci(int n)
{
	if(n <=2)return 1;
	return Fibonacci(n-1)+Fibonacci(n-2);
}

int Fibonacci2(int n)
{
	if(n <=2)return 1;

	int fn1 = 1;
	int fn2 = 1;
	int fn;
	int i;
	for(i = 3;i <= n;i++ )
	{
		fn = fn1+fn2;
		fn2 = fn1;
		fn1 = fn;
	}

	return fn;
}

int main()
{
	printf("%d\n",Fibonacci2(50));
	return 0;
}
