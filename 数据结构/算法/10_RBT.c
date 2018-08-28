#include<stdio.h>
#include<stdlib.h>

enum COLOR{RED,BLACK};

typedef struct node
{
	int nValue;
	int nColor;
	struct node *pLeft;
	struct node *pRight;
	struct node *pFather;
}RBT;

RBT *pRBT = NULL;

RBT *GetUncle(RBT *pNode)
{
	if(pNode == pNode->pFather->pLeft)
	{
		return pNode->pFather->pRight;
	}
	else
	{
		return pNode->pFather->pLeft;
	}
}
	
void InOrderTraversal(RBT *pTree)
{
	if(pTree == NULL)return;
	
	//根左右
	InOrderTraversal(pTree->pLeft);
	printf("color==%d  value==%d\n ",pTree->nColor,pTree->nValue);
	InOrderTraversal(pTree->pRight);
}

void RightRotate(RBT **pTree)
{
	if(*pTree == NULL)return;

	RBT *pMark = (*pTree)->pLeft;
	RBT *pNode = *pTree;
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
		pRBT = pMark;
	}

	//三个父亲关系
	if(pNode->pLeft != NULL)
	{
		pNode->pLeft->pFather = pNode;
	}

	pMark->pFather = pNode->pFather;

	pNode->pFather=pMark;
}

void LeftRotate(RBT **pTree)
{
	if(*pTree == NULL)return;

	RBT *pMark = (*pTree)->pRight;
	RBT *pNode = *pTree;
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
		pRBT = pMark;
	}

	//三个父亲关系
	if(pNode->pRight != NULL)
	{
		pNode->pRight->pFather = pNode;
	}

	pMark->pFather = pNode->pFather;

	pNode->pFather=pMark;
}

RBT *Search(RBT *pTree,int nNum)
{
	if(pTree == NULL)return NULL;
	while(pTree)
	{
		if(pTree->nValue > nNum)
		{
			if(pTree->pLeft == NULL)
			{
				return pTree;
			}
			pTree = pTree->pLeft;
		}
		else if(pTree->nValue < nNum)
		{
			if(pTree->pRight == NULL)
			{
				return pTree;
			}
			pTree = pTree->pRight;
		}
		else
		{
			printf("数据重复！！！\n");
			exit(1);
		}
	}
}

void InsertNode(RBT *pTree,int nNum)
{
	//查找
	RBT *pNode = NULL;
	RBT *pUncle = NULL;
	RBT *pGrandFather = NULL;

	pNode = Search(pTree,nNum);
	
	RBT *pTemp = NULL;
	pTemp = (RBT*)malloc(sizeof(RBT));
	pTemp->nValue = nNum;
	pTemp->nColor = RED;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	pTemp->pFather = NULL;

	//检测情况
	//根
	if(pNode == NULL)
	{
		pRBT = pTemp;
		pRBT->nColor = BLACK;
		return;
	}

	
	pTemp->pFather = pNode;
	if(nNum < pNode->nValue)
	{
		pNode->pLeft = pTemp;
	}
	else
	{
		pNode->pRight = pTemp;
	}

	//父亲是黑色的
	if(pNode->nColor == BLACK)
	{
		return;
	}

	//父亲是红的
	while(pNode->nColor == RED)
	{
		pGrandFather = pNode->pFather;
		pUncle = GetUncle(pNode);

		//叔叔是红的
		if(pUncle != NULL && pUncle->nColor == RED)
		{
			pUncle->nColor = BLACK;
			pNode->nColor = BLACK;
			pGrandFather->nColor = RED;

			pTemp = pGrandFather;

			//更新父亲
			pNode = pTemp->pFather;

			if(pNode == NULL)
			{
				pTemp->nColor = BLACK;
				return;
			}
			continue;
		}

		//叔叔是黑的
		if(pUncle == NULL || pUncle->nColor == BLACK)
		{
			//父亲是爷爷的左
			if(pNode == pGrandFather->pLeft)
			{
				//当前节点是父亲的右
				if(pTemp == pNode->pRight)
				{
					pTemp = pNode;
					pNode = pTemp->pFather;
					LeftRotate(&pTemp);
					continue;
				}

				//当前节点是父亲的左
				if(pTemp == pNode->pLeft)
				{
					pNode->nColor = BLACK;
					pGrandFather->nColor = RED;
					RightRotate(&pGrandFather);
					break;
				}
			}

			//父亲是爷爷的右
			if(pNode == pGrandFather->pRight)
			{
				if(pTemp == pNode->pLeft)
				{
					pTemp = pNode;
					pNode = pTemp->pFather;

					RightRotate(&pTemp);
					continue;
				}

				if(pTemp == pNode->pRight)
				{
					pNode->nColor = BLACK;
					pGrandFather->nColor = RED;
					LeftRotate(&pGrandFather);
					break;
				}
			}
		}
	}
}




void CreateRBT(int arr[],int nLength)
{
	int i;
	for(i = 0;i<nLength;i++)
	{
		InsertNode(pRBT,arr[i]);
	}
}


		

int main()
{
	int arr[] = {11,2,14,1,7,15,5,8};
	CreateRBT(arr,sizeof(arr)/sizeof(arr[0]));
	InOrderTraversal(pRBT);
	printf("========================================\n");
	InsertNode(pRBT,4);
	InOrderTraversal(pRBT);
	return 0;
}
