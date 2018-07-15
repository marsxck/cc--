#include<iostream>
#include<stack>
using namespace std;
typedef struct node {
	int nValue;
	struct node* pLeft;
	struct node* pRight;
}Node;
Node* CreatTree(int i)
{
	if (i < 0)
		return NULL;
	//root
	Node* root = new Node;
	root->nValue = i;
	root->pLeft = CreatTree(i - 1);
	root->pRight = CreatTree(i - 2);
	//root left;
	return root;
}
//Ç°Ðò±éÀú
//µÝ¹é
void preoder(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	cout << pRoot->nValue << " ";
	preoder(pRoot->pLeft);
	preoder(pRoot->pRight);
}
//Ñ­»·
void Preoder(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	stack<Node*> sNode;
	sNode.push(pRoot);
	Node* pTemp = NULL;
	while (!sNode.empty())
	{
		pTemp = sNode.top();
		sNode.pop();
		cout << pTemp->nValue << " ";
		if (pTemp->pRight != NULL)
			sNode.push(pTemp->pRight);
		if (pTemp->pLeft != NULL)
			sNode.push(pTemp->pLeft);
	}
}
//ÖÐÐò±éÀú
//µÝ¹é
void inoder(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	inoder(pRoot->pLeft);
	cout << pRoot->nValue << " ";
	inoder(pRoot->pRight);
}
//Ñ­»·
void Inoder(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	stack<Node*> sNode;
	//sNode.push(pRoot);
	Node* pTemp = pRoot;
	while (pTemp||!sNode.empty())
	{
		if (pTemp)
		{
			sNode.push(pTemp);
			pTemp = pTemp->pLeft;
		}
		else
		{
			pTemp = sNode.top();
			sNode.pop();
			cout << pTemp->nValue << " ";
			pTemp = pTemp->pRight;
		}
	}
}
//ºóÐò
//µÝ¹é
void postoder(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	postoder(pRoot->pLeft);
	postoder(pRoot->pRight);
	cout << pRoot->nValue << " ";
}
//Ñ­»·
void Postorder(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	stack<Node*> sNode;
	stack<int> sValue;
	sNode.push(pRoot);
	while (!sNode.empty())
	{
		Node* pTemp = sNode.top();
		sValue.push(sNode.top()->nValue);
		sNode.pop();
		if (pTemp->pLeft != NULL)
			sNode.push(pTemp->pLeft);
		if (pTemp->pRight != NULL)
			sNode.push(pTemp->pRight);
	}
	while (!sValue.empty())
	{
		cout << sValue.top() << " ";
		sValue.pop();
	}
 
}

void main()
{
	preoder(CreatTree(3));
	cout << "\n";
	Preoder(CreatTree(3));
	cout << "\n";
	inoder(CreatTree(3));
	cout << "\n";
	Inoder(CreatTree(3));
	cout << endl;
	postoder(CreatTree(3));
	cout << endl;
	Postorder(CreatTree(3));
}