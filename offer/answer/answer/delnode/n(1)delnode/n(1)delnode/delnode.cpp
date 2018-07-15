#include<iostream>
using namespace std;
typedef struct node{
	int nValue;
	struct node* pNext;
}Node;
int DelNode(Node** pHead,Node*del)
{
	if (pHead == NULL || del == NULL)
		return -1;
	if (*pHead == del)
	{
		Node* temp = del;
		*pHead = (*pHead)->pNext;
		free(del);
		del = NULL;
	}
	else
	{
		if (del->pNext == NULL)
		{
			Node* temp = *pHead;
			while (temp->pNext->pNext)
			{
				temp = temp->pNext;
			}
			temp->pNext = NULL;
			free(del);
			del = NULL;
		}
		else
		{
			Node* ndel = del->pNext;
			del->nValue = del->pNext->nValue;
			del->pNext = del->pNext->pNext;
			free(ndel);
			ndel = NULL;
		}
	}
}
int main()
{


}