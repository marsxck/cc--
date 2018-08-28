#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int nValue;
	struct node *pNext;
	struct node *pPre;
}Bucket;

void Sort(Bucket *pHead)
{
	if(pHead == NULL|| pHead->pNext == NULL)return;

	Bucket *pUnSort = pHead->pNext; //遍历无序
	Bucket *pSort = NULL;//有序

	int temp;
	while(pUnSort)
	{
		pSort = pUnSort->pPre; //有序的最后一个
		temp = pUnSort->nValue;

		while(pSort != NULL && pSort->nValue > temp)
		{
			pSort->pNext->nValue = pSort->nValue;
			pSort = pSort->pPre;
		}

		if(pSort == NULL)
		{
			pHead->nValue = temp;
		}
		else
		{
			pSort->pNext->nValue = temp;
		}
		pUnSort = pUnSort->pNext;
	}
}


void BucketSort(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return;

	//找到最大值最小值
	int i;
	int nMax;
	int nMin;
	nMax = arr[0];
	nMin = arr[0];
	for(i  =1;i<nLength;i++)
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

	//数字拆位
	int nNum;
	nNum = nMin;
	int nCount = 0;
	while(nNum)
	{
		nCount++;
		nNum/=10;
	}

	nNum = 1;
	while(nCount > 1)
	{
		nNum*=10;
		nCount--;
	}

	//申请桶
	int nMinIndex;
	int nMaxIndex;
	nMinIndex = nMin/nNum;
	nMaxIndex = nMax/nNum;

	Bucket **pBucket = NULL;
	pBucket = (Bucket**)malloc(sizeof(Bucket*)*(nMaxIndex - nMinIndex+1));
	memset(pBucket,0,sizeof(Bucket*)*(nMaxIndex - nMinIndex+1));

	//数据入桶
	Bucket *pTemp = NULL;
	for(i = 0;i<nLength;i++)
	{
		nCount = arr[i]/nNum-nMinIndex;
		pTemp = (Bucket *)malloc(sizeof(Bucket));
		pTemp->nValue = arr[i];
		pTemp->pNext = pBucket[nCount];

		if(pBucket[nCount] != NULL)
		{
			pBucket[nCount]->pPre = pTemp;
		}

		pTemp->pPre = NULL;

		pBucket[nCount] = pTemp;
	}

	//各桶内进行插入排序
	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
	{
		Sort(pBucket[i]);
	}

	//将元素放回原数组
	nCount = 0;
	for(i = 0;i<nMaxIndex - nMinIndex+1;i++)
	{
		//各个链表元素依次放回
		pTemp = pBucket[i];
		while(pTemp)
		{
			arr[nCount] = pTemp->nValue;
			nCount++;
			pTemp = pTemp->pNext;
		}
	}

	//释放
	Bucket *pDel = NULL;
	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
	{
		pTemp = pBucket[i];
		while(pTemp)
		{
			pDel = pTemp;
			pTemp = pTemp->pNext;
			free(pDel);
			pDel = NULL;
		}
	}

	free(pBucket);
	pBucket = NULL;
}

int main()
{
	int arr[] = {102,124,237,309,208,103,280,219,523,404};
	BucketSort(arr,sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
