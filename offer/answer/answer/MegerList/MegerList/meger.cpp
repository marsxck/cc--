#include<stdio.h>
using namespace std;
typedef struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
}ListNode;
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == NULL)
		return pHead2;
	if (pHead2 == NULL)
		return pHead1;
	ListNode* pHead = new ListNode(0);
	if (pHead1->val <= pHead2->val)
	{
		pHead->val = pHead1->val;
		pHead->next = Merge(pHead1->next, pHead2);
	}
	else if (pHead2->val<pHead1->val)
	{
		pHead->val = pHead2->val;
		pHead->next = Merge(pHead1, pHead2->next);
	}
	return pHead;
}