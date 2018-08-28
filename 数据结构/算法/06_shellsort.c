#include<stdio.h>

void ShellSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;

	int nGap;
	int i;
	int j;
	int k;
	int temp;

	//定步长
	for(nGap = nLength/2;nGap >=1;nGap/=2)
	{
		//根据步长分组
		for(i = 0;i<nGap;i++)
		{
			//各组内插入排序
			//遍历无序数组
			for(j = i+nGap;j<nLength;j+=nGap)
			{
				k = j - nGap; //有序最后一个
				temp = arr[j]; //保存无序第一个
				while(temp < arr[k] && k >= i)
				{
					arr[k+nGap] = arr[k];
					k-=nGap;
				}
				//元素放入合适位置
				arr[k+nGap] = temp;
			}
		}
	}
}

int main()
{
	int arr[] = {10,4,7,9,20,3,28,219,523};
	ShellSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
