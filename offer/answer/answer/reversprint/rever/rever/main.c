#include<stdio.h>
#include<stdlib.h>
typedef struct NODE
{
	struct NODE* p;
	int nValue;
}Node;
void AddNode(Node** pHead,int nValue)
{
	if (pHead == NULL)
		return;
	Node* pNode = (Node*)malloc(sizeof(Node));
	pNode->p = NULL;
	pNode->nValue = nValue;
	if (*pHead == NULL)
	{
		*pHead = pNode;
		return;
	}
	else
	{
		Node* pTemp = *pHead;
		while (pTemp->p != NULL)
			pTemp = pTemp->p;
		pTemp->p = pNode;
	}
}
void ReversePrint(Node* pHead)
{
	if (pHead == NULL)
		return;
	ReversePrint(pHead->p);
	printf("%d\t", pHead->nValue);
}
int main()
{
	Node* pHead = NULL;
//	for(int i=0;i<1;i++)
//		AddNode(&pHead,i);
	ReversePrint(pHead);
	 



 }
