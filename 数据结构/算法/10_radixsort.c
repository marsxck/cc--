#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int nValue;
	struct node *pNext;
}Radix;

void LSD(Radix **pRadix,int nBegin,int arr[],int nLength)
{
	//基数
	int nBase = 1;
	while(nBegin > 1)
	{
		nBase*=10;
		nBegin--;
	}

	//数据入桶
	int i;
	Radix *pTemp = NULL;
	Radix *pNode = NULL;
	for(i = 0;i<nLength;i++)
	{
		nBegin = arr[i]/nBase%10;
		pTemp = (Radix*)malloc(sizeof(Radix));
		pTemp->nValue = arr[i];
		pTemp->pNext = NULL;
		
		pNode = pRadix[nBegin];

		//尾添加 
		if(pRadix[nBegin] == NULL)
		{
			pRadix[nBegin] = pTemp;
		}
		else
		{
			while(pNode->pNext != NULL)
			{
				pNode = pNode->pNext;
			}
			pNode->pNext = pTemp;
		}
	}

	//数据放回原数组
	nBegin = 0;
	for(i = 0;i<10;i++)
	{
		pNode = pRadix[i];
		while(pNode)
		{
			arr[nBegin] = pNode->nValue;
			nBegin++;
			pNode = pNode->pNext;
		}
	}

	//小链表释放
	for(i = 0;i<10;i++)
	{
		pNode = pRadix[i];
		while(pNode)
		{
			pTemp = pNode;
			pNode = pNode->pNext;
			free(pTemp);
			pTemp = NULL;
		}
	}

}



		



void RadixSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;
	
	//找最大值
	int i;
	int nMax;
	nMax = arr[0];

	for(i = 1;i<nLength;i++)
	{
		if(arr[i] > nMax)
		{
			nMax = arr[i];
		}
	}

	//获得循环次数
	int nLoopTimes = 0;
	while(nMax)
	{
		nLoopTimes++;
		nMax/=10;
	}

	//申请桶空间
	Radix **pRadix = NULL;
	pRadix = (Radix**)malloc(sizeof(Radix*)*10);
	memset(pRadix,0,sizeof(Radix*)*10);

	//从低位开始入桶
	for(i =1;i<=nLoopTimes;i++)
	{
		LSD(pRadix,i,arr,nLength);
		memset(pRadix,0,sizeof(Radix*)*10);
	}

	free(pRadix);
	pRadix = NULL;
}

int main()
{
	int arr[] = {12,24,237,309,8,103,80,19,53,404};
	RadixSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
