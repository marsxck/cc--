#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CountSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;

	//找最大值和最小值
	int nMin;
	int nMax;
	int i;
	nMin = arr[0];
	nMax = arr[0];
	for(i = 1;i<nLength;i++)
	{
		if(arr[i] < nMin)
		{
			nMin = arr[i];
		}
		if(arr[i] > nMax)
		{
			nMax = arr[i];
		}
	}

	//根据最大值最小值申请计数数组
	int *pCount = NULL;
	pCount = (int*)malloc(sizeof(int)*(nMax-nMin+1));
	memset(pCount,0,sizeof(int)*(nMax-nMin+1));

	//计数
	for(i = 0;i<nLength;i++)
	{
		pCount[arr[i]-nMin]++;
	}

	//向原数组放数据
	int j = 0;
	for(i = 0;i<nMax-nMin +1;i++)
	{
		//计数非零  向原数组对应位置放数据
		while(pCount[i] != 0)
		{
			arr[j] = i + nMin;
			pCount[i]--;
			j++;
		}
	}
	
	//释放
	free(pCount);
	pCount = NULL;
}



int main()
{
	int arr[] = {1,3,6,5,5,6,3,3,3,1,3,5};
	CountSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}
