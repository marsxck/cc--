#include<stdio.h>
#include<stdlib.h>

typedef struct node3
{
	int nValue;
	struct node3 *pNext;
}MyQueue;

typedef struct node4
{
	MyQueue *pHead;
	MyQueue *pTail;
	int nCount;
}Queue;

void q_Init(Queue **pQueue)
{
	*pQueue  = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
	(*pQueue)->nCount = 0;
}

void q_Push(Queue *pQueue,int nNum)
{
	if(pQueue == NULL)return;

	MyQueue *pTemp = NULL;
	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
	pTemp->nValue = nNum;
	pTemp->pNext = NULL;

	if(pQueue->pHead == NULL)
	{
		pQueue->pHead = pTemp;
	}
	else
	{
		pQueue->pTail->pNext = pTemp;
	}
	pQueue->pTail = pTemp;

	pQueue->nCount++;
}

int q_Pop(Queue *pQueue)
{
	if(pQueue == NULL || pQueue->nCount == 0)return -1;

	int nNum;
	MyQueue *pDel = NULL;

	pDel = pQueue->pHead;
	nNum = pDel->nValue;

	pQueue->pHead = pQueue->pHead->pNext;
	free(pDel);
	pDel = NULL;
	pQueue->nCount--;
	
	//只有一个元素被弹出之后 尾置空
	if(pQueue->nCount == 0)
	{
		pQueue->pTail = NULL;
	}
	return nNum;
}

int q_IsEmpty(Queue *pQueue)
{
	if(pQueue == NULL)return -1;
	return pQueue->nCount == 0?1:0;
}

int main()
{
	Queue *pQueue = NULL;
	q_Init(&pQueue);
	q_Push(pQueue,1);
	q_Push(pQueue,2);
	q_Push(pQueue,3);
	q_Push(pQueue,4);

	printf("%d\n",q_Pop(pQueue));
	printf("%d\n",q_Pop(pQueue));
	printf("%d\n",q_Pop(pQueue));
	return 0;
}
