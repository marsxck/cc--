#include<stdio.h>
#include<stdlib.h>

typedef struct node1
{
	int nValue;
	struct node1 *pLeft;
	struct node1 *pRight;
}BinaryTree;

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

typedef struct node
{
	BinaryTree * nValue;
	struct node *pNext;
}MyStack;

typedef struct node2
{
	MyStack *pTop;
	int nCount;
}Stack;

void s_Init(Stack **pStack)
{
	*pStack = (Stack*)malloc(sizeof(Stack));
	(*pStack)->nCount = 0;
	(*pStack)->pTop = NULL;
}

void s_Push(Stack *pStack,BinaryTree* nNum)
{
	if(pStack == NULL)
	{
		printf("stack is not exist.");
		return;
	}

	MyStack *pTemp = NULL;
	pTemp = (MyStack*)malloc(sizeof(MyStack));
	pTemp->nValue = nNum;

	//新来节点的下一个是原来的栈顶
	pTemp->pNext = pStack->pTop;
	pStack->pTop = pTemp;

	//计数器更新
	pStack->nCount++;
}

BinaryTree* s_Pop(Stack *pStack)
{
	if(pStack == NULL || pStack->pTop == NULL)return NULL;

	BinaryTree* nNum = NULL;
	MyStack *pDel = NULL;

	pDel = pStack->pTop;
	nNum = pDel->nValue;
	
	//新栈顶是原来栈顶的下一个
	pStack->pTop = pStack->pTop->pNext;

	pStack->nCount--;
	free(pDel);
	pDel = NULL;
	return nNum;
}

void s_Clear(Stack *pStack)
{
	if(pStack == NULL || pStack->pTop == NULL)return;

	while(pStack->nCount != 0)
	{
		s_Pop(pStack);
	}
}

void s_Destroy(Stack **pStack)
{
	if(*pStack == NULL)return;

	s_Clear(*pStack);
	free(*pStack);
	*pStack = NULL;
}

MyStack *s_GetTop(Stack *pStack)
{
	return pStack->pTop;
}

int s_GetCount(Stack *pStack)
{
	if(pStack == NULL)return -1;
	return pStack->nCount;
}

int s_IsEmpty(Stack *pStack)
{
	if(pStack == NULL)return -1;
	return pStack->nCount == 0 ? 1:0;
}

void UnRecPreOrderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//申请辅助栈
	Stack *pStack = NULL;
	s_Init(&pStack);

	while(1)
	{
		//节点非空 打印 入栈 向左走
		while(pTree)
		{
			printf("%d ",pTree->nValue);
			s_Push(pStack,pTree);
			pTree = pTree->pLeft;
		}

		//栈顶元素弹出
		pTree = s_Pop(pStack);

		//栈空 结束
		if(pTree == NULL)break;

		//栈顶元素的右
		pTree = pTree->pRight;
	}
}
void UnRecInOrderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//申请辅助栈
	Stack *pStack = NULL;
	s_Init(&pStack);

	while(1)
	{
		//节点非空 打印 入栈 向左走
		while(pTree)
		{
			s_Push(pStack,pTree);
			pTree = pTree->pLeft;
		}

		//栈顶元素弹出
		pTree = s_Pop(pStack);

		//栈空 结束
		if(pTree == NULL)break;

		printf("%d ",pTree->nValue);

		//栈顶元素的右
		pTree = pTree->pRight;
	}
}
void UnRecLastOrderTraversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	//申请辅助栈
	Stack *pStack = NULL;
	s_Init(&pStack);
	BinaryTree *pMark = NULL;

	while(1)
	{
		//节点非空 入栈 向左走
		while(pTree)
		{
			s_Push(pStack,pTree);
			pTree = pTree->pLeft;
		}

		//栈 空 结束
		if(pStack->pTop == NULL)break;

		//检测栈顶元素的右
		if(pStack->pTop->nValue->pRight == NULL || pStack->pTop->nValue->pRight == pMark)
		{
			//弹出 打印 标记
			pMark = s_Pop(pStack);
			printf("%d ",pMark->nValue);
		}
		else
		{
			//处理栈顶元素的右
			pTree = pStack->pTop->nValue->pRight;
		}
	}
}

		

int main()
{
	BinaryTree *pTree = NULL;
	pTree = CreateBiTree();
	UnRecPreOrderTraversal(pTree);
	printf("\n");
	UnRecInOrderTraversal(pTree);
	printf("\n");
	UnRecLastOrderTraversal(pTree);
	return 0;
}
