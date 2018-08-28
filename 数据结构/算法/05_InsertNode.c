#include<stdio.h>
#include<stdlib.h>

enum DIRECTION{LEFT,RIGHT};

typedef struct node
{
	int nValue;
	struct node *pLeft;
	struct node *pRight;
}BinaryTree;
typedef struct node3
{
	BinaryTree * nValue;
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

void q_Push(Queue *pQueue,BinaryTree* nNum)
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

BinaryTree * q_Pop(Queue *pQueue)
{
	if(pQueue == NULL || pQueue->nCount == 0)return NULL;

	BinaryTree * nNum = NULL;
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

BinaryTree *CreateBiTree()
{
	BinaryTree *pRoot = NULL;

	//根
	pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->nValue = 1;

	//根的左
	pRoot->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->nValue = 2;

	//左的左
	pRoot->pLeft->pLeft =  (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->pLeft->nValue = 4;
	pRoot->pLeft->pLeft->pLeft = NULL;
	pRoot->pLeft->pLeft->pRight = NULL;

	//左的右
	pRoot->pLeft->pRight =  (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->pRight ->nValue = 5;
	pRoot->pLeft->pRight->pLeft = NULL;
	pRoot->pLeft->pRight->pRight = NULL;

	//根的右
	pRoot->pRight =  (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pRight->nValue = 3;
	pRoot->pRight->pLeft = NULL;
	pRoot->pRight->pRight = NULL;

	return pRoot;
}


void PreOrderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//根
	printf("%d\n",pTree->nValue);
	//左
	PreOrderTraversal(pTree->pLeft);
	//右
	PreOrderTraversal(pTree->pRight);
}

BinaryTree * LevelSearch(BinaryTree *pTree,int nNum)
{
	if(pTree == NULL)return NULL;

	//申请辅助队列
	Queue *pQueue = NULL;
	q_Init(&pQueue);

	//根入队
	q_Push(pQueue,pTree);

	//循环处理剩余节点
	while(!q_IsEmpty(pQueue))
	{
		pTree = q_Pop(pQueue);
		if(pTree->nValue == nNum)
		{
			return pTree;
		}

		//左右非空入队
		if(pTree->pLeft != NULL)
		{
			q_Push(pQueue,pTree->pLeft);
		}
		if(pTree->pRight != NULL)
		{
			q_Push(pQueue,pTree->pRight);
		}
	}
	return NULL;
}

void InsertNode(BinaryTree *pTree,int nNum,int nDirection,int nValue)
{
	if(pTree == NULL)return;

	//查找
	BinaryTree *pNode = NULL;
	pNode = LevelSearch(pTree,nNum);

	if(pNode == NULL)return;

	//节点放入
	BinaryTree *pTemp = NULL;
	pTemp = (BinaryTree*)malloc(sizeof(BinaryTree));
	pTemp->nValue = nValue;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;

	//左右
	if(nDirection == LEFT)
	{
		if(pNode->pLeft == NULL)
		{
			pNode->pLeft = pTemp;
			return;
		}
		else
		{
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}
	else
	{
		if(pNode->pRight == NULL)
		{
			pNode->pRight = pTemp;
			return;
		}
		else
		{
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}
}
	


int main()
{
	BinaryTree *pRoot = NULL;
	pRoot = CreateBiTree();
	PreOrderTraversal(pRoot);
	printf("----------------------------\n");
	InsertNode(pRoot,2,1,10000);
	PreOrderTraversal(pRoot);
	return 0;
}
