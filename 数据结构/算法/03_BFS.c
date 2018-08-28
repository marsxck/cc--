#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	int nVertex;
	int nEdge;
	int *pMatrix;
}Graph;
typedef struct node3
{
	int nValue;
	struct node3 *pNext;
}MyQueue;

typedef struct node4
{
	MyQueue *pHead;
	MyQueue *pTail;
	int nCount;
}Queue;

void q_Init(Queue **pQueue)
{
	*pQueue  = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
	(*pQueue)->nCount = 0;
}

void q_Push(Queue *pQueue,int nNum)
{
	if(pQueue == NULL)return;

	MyQueue *pTemp = NULL;
	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
	pTemp->nValue = nNum;
	pTemp->pNext = NULL;

	if(pQueue->pHead == NULL)
	{
		pQueue->pHead = pTemp;
	}
	else
	{
		pQueue->pTail->pNext = pTemp;
	}
	pQueue->pTail = pTemp;

	pQueue->nCount++;
}

int q_Pop(Queue *pQueue)
{
	if(pQueue == NULL || pQueue->nCount == 0)return -1;

	int nNum;
	MyQueue *pDel = NULL;

	pDel = pQueue->pHead;
	nNum = pDel->nValue;

	pQueue->pHead = pQueue->pHead->pNext;
	free(pDel);
	pDel = NULL;
	pQueue->nCount--;
	
	//只有一个元素被弹出之后 尾置空
	if(pQueue->nCount == 0)
	{
		pQueue->pTail = NULL;
	}
	return nNum;
}

int q_IsEmpty(Queue *pQueue)
{
	if(pQueue == NULL)return -1;
	return pQueue->nCount == 0?1:0;
}

Graph *CreateGraph()
{
	Graph *pGraph = NULL;
	pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->nVertex = 0;
	pGraph->nEdge = 0;
	pGraph->pMatrix = NULL;

	int nV;
	int nE;

	//输入顶点个数和边的条数
	printf("please input the number of nV.\n");
	scanf("%d",&nV);
	printf("please input the number of nE.\n");
	scanf("%d",&nE);

	pGraph->nVertex = nV;
	pGraph->nEdge = nE;

	//根据顶点个数申请矩阵
	pGraph->pMatrix = (int*)malloc(sizeof(int)*nV*nV);
	memset(pGraph->pMatrix,0,sizeof(int)*nV*nV);
	
	int va,vb;
	//根据边的条数来给矩阵赋值
	int i;
	for(i = 1;i<=nE;i++)
	{
		//输入两个顶点确定一条边
		printf("please input two vertexs.\n");
		scanf("%d%d",&va,&vb);
		//顶点要在合理范围之内 最后的检测 是 如果对应边已经存在 则 不重复赋值
		if(va <= nV && va >=1 && vb <= nV && vb >=1 && pGraph->pMatrix[(va - 1)*nV + (vb - 1)] == 0)
		{
			//（1，2） （ 2，1) 是同一条边  两个位置均要赋值
			pGraph->pMatrix[(va-1)*nV+(vb-1)] = 1;
			pGraph->pMatrix[(vb-1)*nV+(va-1)] = 1;
		}
		//输入有误  浪费一条边 要减回来
		else
		{
			printf("input error,please try again.\n");
			i--;
		}
	}

	return pGraph;
}

void BFS(Graph *pGraph,int nBegin)
{
	//申请辅助队列
	Queue *pQueue = NULL;
	q_Init(&pQueue);

	//申请标记数组
	int *pMark = NULL;
	pMark = (int*)malloc(sizeof(int)*pGraph->nVertex);
	memset(pMark,0,sizeof(int)*pGraph->nVertex);

	q_Push(pQueue,nBegin);
	pMark[nBegin-1] = 1;

	int i;
	while(!q_IsEmpty(pQueue))
	{
		//弹出打印
		nBegin = q_Pop(pQueue);
		printf("%d ",nBegin);

		//相关顶点入队
		for(i = 0;i<pGraph->nVertex;i++)
		{
			if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex + i] == 1 
				&& pMark[i] == 0)
			{
				q_Push(pQueue,i+1);
				pMark[i] = 1;
			}
		}
	}
}



int main()
{
	Graph *pGraph = NULL;
	pGraph = CreateGraph();

	BFS(pGraph,5);	
	return 0;
}
