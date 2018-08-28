#include<iostream>
#include<stdlib.h>
using namespace std;
int main()
{
	int n;//记录个数
	cin >> n;
	int *martix = (int*)calloc(n*n,sizeof(int));//申请矩阵

	int *index = (int*)calloc(n,sizeof(int));//申请数组记录关系
	int flag = 0;
	//根据输入确立矩阵
	for (int i = 0; i<n; i++)
	{
		while (cin >> *(index + flag))
		{
			if (*(index + flag) == 0)
				break;
			flag++;
		}
		flag = 0;
		while (*(index + flag) != 0)
		{
			martix[i*n + *(index + flag)-1] = 1;
			martix[*(index + flag)*n-n+i] = 1;
			flag++;
		}
		flag = 0;
	}
	//计算组数
	//查找行
	int res=1;
	flag = 0;
	for (int i=0;i<n;i++)
	{
		flag = 0;
		for (int j = 0; j < n; j++)
		{
			if (martix[i*n + j] != 0)
			{
				flag = 1;
			}
		}
		if(flag==0)
			res++;
	}
	return res;
}