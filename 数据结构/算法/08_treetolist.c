#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int nValue;
	struct node *pLeft;
	struct node *pRight;
}BinaryTree;


void AddNode(BinaryTree **pTree,int nNum)
{
	BinaryTree *pTemp = NULL;
	pTemp = (BinaryTree*)malloc(sizeof(BinaryTree));
	pTemp->nValue = nNum;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;

	//空树 新来节点就是根节点
	if(*pTree == NULL)
	{
		*pTree = pTemp;
		return;
	}

	//非空
	BinaryTree *pNode = NULL;
	pNode = *pTree;

	//遍历树 找到合适位置放入
	while(pNode)
	{
		//当前节点的值 比新来的大 
		if(pNode->nValue > nNum)
		{
			//新来节点放当前节点左侧
			if(pNode->pLeft == NULL)
			{
				pNode->pLeft = pTemp;
				return;
			}
			else
			{
				pNode = pNode->pLeft;
			}
		}
		//当前节点的值比新来的小
		else if(pNode->nValue < nNum)
		{
			//新来节点放右侧
			if(pNode->pRight == NULL)
			{
				pNode->pRight = pTemp;
				return;
			}
			else
			{
				pNode = pNode->pRight;
			}
		}
		//相等 异常
		else
		{
			printf("error.\n");
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}
}




BinaryTree *CreateBST(int arr[],int nLength)
{
	if(arr == NULL || nLength <=0)return NULL;

	BinaryTree *pRoot = NULL;
	int i;
	for(i = 0;i<nLength;i++)
	{
		AddNode(&pRoot,arr[i]);
	}
	return pRoot;
}

void Traversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;

	Traversal(pTree->pLeft);
	printf("%d ",pTree->nValue);
	Traversal(pTree->pRight);
}


void TreeToList(BinaryTree *pTree,BinaryTree **pHead,BinaryTree **pTail)
{
	if(pTree == NULL)return;

	//按照中序遍历
	//遍历到的节点依次添加到双向链表中
	TreeToList(pTree->pLeft,pHead,pTail);

	//节点添加
	if(*pHead == NULL)
	{
		*pHead = pTree;
	}
	else
	{
		(*pTail)->pRight = pTree;
		pTree->pLeft = *pTail;
	}
	*pTail = pTree;

	TreeToList(pTree->pRight,pHead,pTail);
}

void Print(BinaryTree *pHead)
{
	while(pHead)
	{
		printf("%d ",pHead->nValue);
		pHead  =pHead->pRight;
	}
}

int main()
{
	int arr[] = {10,3,20,38,2,19,87};
	BinaryTree *pTree = NULL;
	pTree = CreateBST(arr,sizeof(arr)/sizeof(arr[0]));
	Traversal(pTree);
	printf("\n");
	BinaryTree *pHead = NULL;
	BinaryTree *pTail = NULL;
	TreeToList(pTree,&pHead,&pTail);
	Print(pHead);
	return 0;
}
