#include<stdio.h>
#include<stdlib.h>

void Merge(int arr[],int nLow,int nHigh)
{
	int nBegin1;
	int nEnd1;
	int nBegin2;
	int nEnd2;

	nBegin1 = nLow;
	nEnd1 = (nHigh-nLow)/2+nLow;
	nBegin2 = nEnd1 + 1;
	nEnd2 = nHigh;

	//辅助空间申请
	int *pTemp = NULL;
	pTemp = (int*)malloc(sizeof(int)*(nHigh-nLow+1));
	int i;
	i = 0;

	//合并
	while(nBegin1 <= nEnd1 && nBegin2 <= nEnd2)
	{
		if(arr[nBegin1] < arr[nBegin2])
		{
			pTemp[i] = arr[nBegin1];
			nBegin1++;
		}
		else
		{
			pTemp[i] = arr[nBegin2];
			nBegin2++;
		}
		i++;
	}

	//将有剩余的数据依次放入
	while(nBegin1 <= nEnd1)
	{
		pTemp[i] = arr[nBegin1];
		i++;
		nBegin1++;
	}

	while(nBegin2 <= nEnd2)
	{
		pTemp[i] = arr[nBegin2];
		i++;
		nBegin2++;
	}

	//临时数组元素放回原数组
	for(i = 0;i<nHigh-nLow+1;i++)
	{
		arr[i+nLow] = pTemp[i];
	}

	//空间释放
	free(pTemp);
	pTemp = NULL;
}

void MergeSort(int arr[],int nLow,int nHigh)
{
	if(arr == NULL || nLow >= nHigh)return;

	//先拆分
	//两路归并
	int nMid;
	nMid = (nHigh-nLow)/2+nLow;
	MergeSort(arr,nLow,nMid);
	MergeSort(arr,nMid+1,nHigh);

	//合并
	Merge(arr,nLow,nHigh);
}

int main()
{
	int arr[] = {2,1,5,7,6,8};
	MergeSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
