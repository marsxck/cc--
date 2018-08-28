#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int nValue;
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

void s_Push(Stack *pStack,int nNum)
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

int s_Pop(Stack *pStack)
{
	if(pStack == NULL || pStack->pTop == NULL)return -1;

	int nNum;
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

int main()
{
	Stack *pStack = NULL;
	s_Init(&pStack);

	s_Push(pStack,1);
	s_Push(pStack,2);
	s_Push(pStack,3);
	s_Push(pStack,4);

	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));


	s_Destroy(&pStack);
	s_Push(pStack,1000);
	return 0;
}
