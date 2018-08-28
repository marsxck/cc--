#include<stdio.h>

void InsertSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;

	int i;//无序数组的第一个
	int j;//有序数组的最后一个
	int temp;//保存无序元素

	for(i = 1;i<nLength;i++)
	{
		j = i-1;
		temp = arr[i];

		//向前遍历有序数组
		while(temp < arr[j] && j>=0)
		{
			arr[j +1] = arr[j];
			j--;
		}

		//将无序元素放入到在有序数组中的合适位置
		arr[j+1] = temp;
	}
}

int main()
{
	int arr[] = {10,4,7,9,20,3,28,219,523};
	InsertSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
