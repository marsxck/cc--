#include<iostream>
void Adjust(int arr[],int nLength,int Root)
{
	int max;
	for (int i=Root*2+1;i<=nLength-1;i=Root*2+1)
	{
		max = i;
		//两个子节点比较，选出最大值
		if (i + 1 <= nLength - 1)
		{
			if (arr[i] < arr[i + 1])
				max = i + 1;
		}
		if (arr[Root]<arr[max])
		{
			arr[Root] = arr[Root] ^ arr[max];
			arr[max] = arr[Root] ^ arr[max];
			arr[Root] = arr[Root] ^ arr[max];
			Root = max;
		}
		else
		{
			break;
		}
	}
}
int main()
{
	int arr[] = { 2,1,5,4,3 };
	//初始化堆,从下-上
	int nLength = sizeof(arr) / sizeof(arr[0]);
	for (int i = nLength / 2 - 1; i >= 0; i--)
	{
		Adjust(arr, nLength, i);
	}
	//堆排序
	for (int i=nLength-1;i>0;i--)
	{
		arr[0] = arr[0] ^ arr[i];
		arr[i] = arr[0] ^ arr[i];
		arr[0] = arr[0] ^ arr[i];
		Adjust(arr,i,0);
	}
	return 0;
}