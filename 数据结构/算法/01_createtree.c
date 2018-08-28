#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int nValue;
	struct node *pLeft;
	struct node *pRight;
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

void CreateBinaryTree(BinaryTree **pTree)
{
	//输入数据
	int nNum;
	scanf("%d",&nNum);

	//检测
	if(nNum == 0)return;

	//申请节点
	*pTree = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pTree)->nValue = nNum;
	(*pTree)->pLeft = NULL;
	(*pTree)->pRight = NULL;

	//处理左右
	CreateBinaryTree(&((*pTree)->pLeft));
	CreateBinaryTree(&((*pTree)->pRight));
}


BinaryTree *ArrToTree(int arr[],int nLength)
{
	if(arr == NULL || nLength <= 0) return NULL;

	//申请空间
	BinaryTree *pTree = NULL;
	pTree = (BinaryTree*)malloc(nLength*sizeof(BinaryTree));

	//赋值
	int i;
	for(i = 0;i<nLength;i++)
	{
		pTree[i].nValue = arr[i];
		pTree[i].pLeft = NULL;
		pTree[i].pRight = NULL;
	}

	//父子关系关联
	for(i = 0;i<= nLength/2 -1;i++)
	{
		if(2*i + 1 <= nLength-1)
		{
			pTree[i].pLeft = &pTree[2*i+1];
		}
		if(2*i +2 <= nLength -1)
		{
			pTree[i].pRight = &pTree[2*i+2];
		}
	}

	return pTree;
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

int main()
{
	BinaryTree *pRoot = NULL;
	//pRoot = CreateBiTree();
	//CreateBinaryTree(&pRoot);

	int arr[] = {1,2,3,4,5,6};
	pRoot = ArrToTree(arr,sizeof(arr)/sizeof(arr[0]));

	PreOrderTraversal(pRoot);
	return 0;
}
