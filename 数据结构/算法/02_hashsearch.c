#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int nValue;
	int nIndex;
	struct node *pNext;
}Hash;

Hash **CreateHashTable(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return NULL;

	//申请表头
	Hash **pHash = (Hash**)malloc(sizeof(Hash*)*nLength);
	memset(pHash,0,sizeof(Hash*)*nLength);

	//元素入表
	int i;
	Hash *pTemp = NULL;
	int nIndex;
	for(i = 0;i<nLength;i++)
	{
		nIndex = arr[i] % nLength;
		pTemp = (Hash*)malloc(sizeof(Hash));
		pTemp->nValue = arr[i];
		pTemp->nIndex = i;
		
		//拉链法 头添加
		pTemp->pNext = pHash[nIndex];
		pHash[nIndex] = pTemp;
	}

	return pHash;
}

int HashSearch(Hash **pHash,int nLength,int nNum)
{
	int nIndex;
	nIndex = nNum%nLength;

	//遍历对应位置链表
	Hash *pNode = NULL;
	pNode = pHash[nIndex];
	while(pNode)
	{
		if(pNode->nValue == nNum)
		{
			return pNode->nIndex;
		}
		pNode = pNode->pNext;
	}
	return -1;
}

void Destroy(Hash **pHash,int nLength)
{
	//依次释放小链表
	int i;
	Hash *pDel = NULL;
	Hash *pMark = NULL;
	for(i = 0;i<nLength;i++)
	{
		pMark = pHash[i];
		while(pMark)
		{
			pDel = pMark;
			pMark = pMark->pNext;
			free(pDel);
			pDel = NULL;
		}
	}

	//释放表头
	free(pHash);
	pHash = NULL;
}


int main()
{
	int arr[] = {10,28,29,18,4,5,68,209,55,78};
	Hash **pHash = CreateHashTable(arr,sizeof(arr)/sizeof(arr[0]));

	int n = HashSearch(pHash,sizeof(arr)/sizeof(arr[0]),55);
	printf("%d\n",n);
	Destroy(pHash,sizeof(arr)/sizeof(arr[0]));
	pHash = NULL;
	return 0;
}
