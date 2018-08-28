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

//查找被删除节点及其父亲 树  被删除节点 被删除节点的父亲 查找谁
void FindNode(BinaryTree *pTree,BinaryTree **pDel,BinaryTree **pDelFather,int nNum)
{
	while(pTree)
	{
		//找到了 返回
		if(pTree->nValue == nNum)
		{
			*pDel = pTree;
			return;
		}
		//当前节点值比被查找的大  去树的左边继续查找
		else if(pTree->nValue > nNum)
		{
			*pDelFather = pTree;
			pTree = pTree->pLeft;
		}
		//去右边
		else
		{
			*pDelFather = pTree;
			pTree = pTree->pRight;
		}
	}

	//失败
	printf("failed.\n");
	exit(1);
}

void DelNode(BinaryTree **pTree,int nNum)
{
	if(*pTree == NULL )return;

	//查找
	BinaryTree *pNode = NULL;
	BinaryTree *pDelFather = NULL;

	FindNode(*pTree,&pNode,&pDelFather,nNum);
	
	BinaryTree *pMark = NULL;
	//删除节点情况
	//两个孩子
	if(pNode->pLeft!= NULL && pNode->pRight != NULL)
	{
		//左子树最右
		//向左走
		//标记原删除位置
		pMark = pNode;
		pDelFather = pNode;
		pNode = pNode->pLeft;

		//找最右
		while(pNode->pRight != NULL)
		{
			pDelFather = pNode;
			pNode = pNode->pRight;
		}

		//新删除位置值 覆盖 原删除位置
		pMark->nValue = pNode->nValue;
	}

	//删除一个 或  零个
	//被删除节点是根
	if(pDelFather == NULL)
	{
		*pTree = (pNode->pLeft != NULL)?pNode->pLeft:pNode->pRight;
		free(pNode);
		pNode = NULL;
		return;
	}
	else
	{
		//被删除节点是父亲的左
		if(pNode == pDelFather->pLeft)
		{
			pDelFather->pLeft = pNode->pLeft?pNode->pLeft:pNode->pRight;
		}
		//被删除节点是父亲的右
		else
		{
			pDelFather->pRight = pNode->pLeft?pNode->pLeft:pNode->pRight;
		}
		free(pNode);
		pNode = NULL;
		return;
	}
}



int main()
{
	int arr[] = {10,3,20,38,2,19,87};
	BinaryTree *pTree = NULL;
	pTree = CreateBST(arr,sizeof(arr)/sizeof(arr[0]));
	Traversal(pTree);
	printf("\n");
	DelNode(&pTree,20);
	Traversal(pTree);
	return 0;
}
