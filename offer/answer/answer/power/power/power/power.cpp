#include<stdio.h>
bool equal(double num1,double num2)
{
	if ((num1 - num2) < 0.0000001 && (num1 - num2) > -0.0000001)
		return true;
	else
		return false;
}
double Pow(double base,int ex)
{
	//错误处理
	if (equal(base, 0.0) && ex < 0)
	{
		return 0.0;
	}
	//正负指数
	int absex = ex;
	if (ex < 0)
	{
		absex = -ex;
	}
	double res = 1.0;
	for (int i = 0; i < absex; i++)
	{
		res *= base;
	}
	if (ex < 0)
	{
		return 1 / res;
	}
	return res;
}
double PowCore(double base,int ex)
{
	if (ex == 0)
		return 1.0;
	if (ex == 1)
		return base;
	double res = PowCore(base, ex >> 1);
	res*=res;
	if (ex & 0x01 == 1)
		res *= base;
	return res;
}
void main()
{

	printf("%f", Pow(-2, 3));
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               }