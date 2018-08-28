#include<stdio.h>

int Sort(int arr[],int nLow,int nHigh)
{
	int nStandard;
	nStandard = arr[nLow];

	while(nLow < nHigh)
	{
		//从后向前找比标准值小的
		while(nLow < nHigh)
		{
			if(arr[nHigh] < nStandard)
			{
				//将找到的小值 放入前面的坑里
				arr[nLow] = arr[nHigh];
				nLow++;
				break;
			}
			nHigh--;
		}
		
		//从前向后找比标准值大的
		while(nLow < nHigh)
		{
			if(arr[nLow] > nStandard)
			{
				//将找到的值放入后面的坑里
				arr[nHigh] = arr[nLow];
				nHigh--;
				break;
			}
			nLow++;
		}
	}

	//将标准值放入对应位置
	arr[nLow] = nStandard;

	//返回标准值
	return nLow;
}

int Sort2(int arr[],int nLow,int nHigh)
{
	int nSmall;
	nSmall = nLow-1;

	//遍历数组元素 
	for(nLow;nLow < nHigh;nLow++)
	{
		if(arr[nLow] < arr[nHigh])
		{
			//小区间扩张
			if(++nSmall != nLow)
			{
				arr[nSmall] = arr[nSmall] ^ arr[nLow];
				arr[nLow] = arr[nSmall] ^ arr[nLow];
				arr[nSmall] = arr[nSmall] ^ arr[nLow];
			}
		}
	}

	//将标准值放入合适位置 (小区间的下一个)
	if(++nSmall != nHigh)
	{
		arr[nSmall] = arr[nSmall]^arr[nHigh];
		arr[nHigh] = arr[nSmall]^arr[nHigh];
		arr[nSmall] = arr[nSmall]^arr[nHigh];
	}

	//返回标准值位置
	return nSmall;
}

void QuickSort(int arr[],int nLow,int nHigh)
{
	if(arr == NULL)return;

	if(nLow >= nHigh)return;

	//找到标准值位置
	int nStandard;
	
	nStandard = Sort(arr,nLow,nHigh);

	//根据标准值位置将当前数组分割成两部分 各部分分别执行以上操作
	QuickSort(arr,nLow,nStandard-1);
	QuickSort(arr,nStandard+1,nHigh);
}

int main()
{
	int arr[] = {2,1,5,7,6,8};
	QuickSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
