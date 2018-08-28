#include<stdio.h>

#define LEFT 2*nRootID +1
#define RIGHT 2*nRootID+2
void Adjust(int arr[],int nLength,int nRootID)
{
	while(1)
	{
		//两个孩子
		if(RIGHT < nLength)
		{
			//比较两个孩子大小
			if(arr[LEFT] > arr[RIGHT])
			{
				//大的和父亲比
				if(arr[LEFT] > arr[nRootID])
				{
					arr[LEFT]  =arr[LEFT]^ arr[nRootID];
					arr[nRootID]  =arr[LEFT]^ arr[nRootID];
					arr[LEFT]  =arr[LEFT]^ arr[nRootID];

					nRootID = LEFT;
					continue;
				}
				break;
			}
			else
			{
				if(arr[RIGHT] > arr[nRootID])
				{
					arr[RIGHT] = arr[RIGHT]^arr[nRootID];
					arr[nRootID] = arr[RIGHT]^arr[nRootID];
					arr[RIGHT] = arr[RIGHT]^arr[nRootID];

					nRootID = RIGHT;
					continue;
				}
				break;
			}
		}
		//一个孩子
		else if(LEFT < nLength)
		{
			if(arr[LEFT] > arr[nRootID])
			{
				arr[LEFT]  =arr[LEFT]^ arr[nRootID];
				arr[nRootID]  =arr[LEFT]^ arr[nRootID];
				arr[LEFT]  =arr[LEFT]^ arr[nRootID];

				nRootID = LEFT;
				continue;
			}
			break;
		}
		//没有孩子
		else
		{
			break;
		}
	}
}
void Adjust2(int arr[],int nLength,int nRootID)
{
	int MAX;
	for(MAX = LEFT;MAX < nLength; MAX = LEFT )
	{
		//如果有两个孩子
		if(RIGHT < nLength)
		{
			if(arr[MAX] < arr[RIGHT])
			{
				MAX = RIGHT;
			}
		}

		//大的和父亲比
		if(arr[MAX] > arr[nRootID])
		{
			arr[MAX] = arr[MAX]^arr[nRootID];
			arr[nRootID] = arr[MAX]^arr[nRootID];
			arr[MAX] = arr[MAX]^arr[nRootID];

			nRootID = MAX;
		}
		else
		{
			break;
		}
	}
}



void HeapSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;

	//创建初始堆
	int i;
	for(i = nLength/2-1;i>=0;i--)
	{
		//调整各个父亲节点
		Adjust2(arr,nLength,i);
	}

	//排序
	for(i = nLength-1;i>0;i--)
	{
		//堆顶和最后位置交换
		arr[0] = arr[0] ^ arr[i];
		arr[i] = arr[0] ^ arr[i];
		arr[0] = arr[0] ^ arr[i];

		//重新调整堆顶
		Adjust2(arr,i,0);
	}
}

int main()
{
	int arr[] = {10,4,7,9,20,3,28,219,523};
	HeapSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
