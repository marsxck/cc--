#include<iostream>
typedef struct Node {
	int nValue;
	struct Node* pLeft;
	struct Node* pRight;
	Node()
	{
		pLeft = NULL;
		pRight = NULL;
	}
};
Node* construct(int* preoder,int* inorder,int nlength)
{
	if (preoder == NULL || inorder == NULL || nlength <= 0)
		return NULL;
	//确定根节点
	Node* pRoot = new Node;
	pRoot->nValue = preoder[0];
	//是否递归结束
	if (nlength == 1)
	{
		if (*preoder == *inorder)
			return pRoot;
		else
		{
			std::cout << "error" << std::endl;
			return NULL;
		}
	}
	//确定左右子树
	int nLeftnum = 0;
	int nRightnum = 0;
	int i;
	for (int i = 0; i < nlength; i++)
	{
		if (preoder[0] == inorder[i])
		{
			break;
		}
		nLeftnum++;
	}
	nRightnum = nlength - nLeftnum - 1;
	if (nLeftnum > 0)
		pRoot->pLeft=construct(preoder+1, inorder, nLeftnum);
	if (nRightnum > 0) 
		pRoot->pRight=construct(preoder+nLeftnum+1,inorder+nLeftnum+1,nRightnum);
	return pRoot;
}
void print(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	std::cout << pRoot->nValue << " ";
	print(pRoot->pLeft);
	print(pRoot->pRight);
}
int main()
{
	int a[] = {1, 2, 4,7,3,5,6,8};
	int b[] = {4,7,2,1,5,3,8,6};
	Node* p = construct(a, b, 8);
	print(p);
	

}