#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int nValue;
	struct node *pLeft;
	struct node *pRight;
	struct node *pFather;
}BinaryTree;

BinaryTree *CreateBiTree()
{
	BinaryTree *pRoot = NULL;

	//根
	pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->nValue = 1;
	pRoot->pFather = NULL;

	//根的左
	pRoot->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->nValue = 2;
	pRoot->pLeft->pFather = pRoot;

	//左的左
	pRoot->pLeft->pLeft =  (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->pLeft->nValue = 4;
	pRoot->pLeft->pLeft->pFather = pRoot->pLeft;
	pRoot->pLeft->pLeft->pLeft = NULL;
	pRoot->pLeft->pLeft->pRight = NULL;

	//左的右
	pRoot->pLeft->pRight =  (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pLeft->pRight ->nValue = 5;
	pRoot->pLeft->pRight->pFather = pRoot->pLeft;
	pRoot->pLeft->pRight->pLeft = NULL;
	pRoot->pLeft->pRight->pRight = NULL;

	//根的右
	pRoot->pRight =  (BinaryTree*)malloc(sizeof(BinaryTree));
	pRoot->pRight->nValue = 3;
	pRoot->pRight->pFather = pRoot;
	pRoot->pRight->pLeft = NULL;
	pRoot->pRight->pRight = NULL;

	return pRoot;
}

void RightRotate(BinaryTree **pTree)
{
	if(*pTree == NULL)return;

	BinaryTree *pNode = *pTree; //支点
	BinaryTree *pMark = pNode->pLeft; //轴

	//三个孩子关系
	pNode->pLeft = pMark->pRight;
	pMark->pRight = pNode;
	if(pNode->pFather != NULL)
	{
		if(pNode == pNode->pFather->pLeft)
		{
			pNode->pFather->pLeft = pMark;
		}
		else
		{
			pNode->pFather->pRight = pMark;
		}
	}
	else
	{
		//根
		*pTree = pMark;
	}

	//三个父亲关系
	if(pNode->pLeft != NULL)
	{
		pNode->pLeft->pFather = pNode;
	}
	pMark->pFather = pNode->pFather;
	pNode->pFather = pMark;
}

void LeftRotate(BinaryTree **pTree)
{
	if(*pTree == NULL)return;

	BinaryTree *pNode = *pTree; //支点
	BinaryTree *pMark = pNode->pRight; //轴

	//三个孩子关系
	pNode->pRight = pMark->pLeft;
	pMark->pLeft = pNode;
	if(pNode->pFather != NULL)
	{
		if(pNode == pNode->pFather->pLeft)
		{
			pNode->pFather->pLeft = pMark;
		}
		else
		{
			pNode->pFather->pRight = pMark;
		}
	}
	else
	{
		//根
		*pTree = pMark;
	}

	//三个父亲关系
	if(pNode->pRight != NULL)
	{
		pNode->pRight->pFather = pNode;
	}
	pMark->pFather = pNode->pFather;
	pNode->pFather = pMark;
}
void Traversal(BinaryTree *pTree)
{
	if(pTree == NULL)return;
	printf("%d\n",pTree->nValue);
	Traversal(pTree->pLeft);
	Traversal(pTree->pRight);
}


int main()
{
	BinaryTree *pTree = NULL;
	pTree = CreateBiTree();
	RightRotate(&pTree);
	Traversal(pTree);
	printf("-------\n");
	LeftRotate(&pTree);
	Traversal(pTree);
	return 0;
}
