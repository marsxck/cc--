#include<stdio.h>

void BubbleSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;

	int i;
	int j;
	int nFlag = 0;
	for(i = 0;i<nLength-1;i++)
	{
		nFlag = 0;
		for(j = 0;j<nLength-i-1;j++)
		{
			//前面元素比后面大 交换
			if(arr[j] > arr[j+1])
			{
				arr[j] = arr[j] ^ arr[j+1];
				arr[j+1] = arr[j] ^ arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];

				//发生交换要标记 标记本次最大交换位置 方便下次操作
				nFlag = j+1;
			}
		}
		if(nFlag == 0)break;

		//根据上次最大交换位置减少下次 执行趟数 以及减少下次遍历的元素个数
		i = nLength-nFlag-1;
	}
}

int main()
{
	int arr[] = {10,4,7,9,20,3,28,219,523};
	BubbleSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
