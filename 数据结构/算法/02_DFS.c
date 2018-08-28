#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	int nVertex;
	int nEdge;
	int *pMatrix;
}Graph;

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

void MyDFS(Graph *pGraph,int nBegin,int *pMark)
{
	//顶点打印 标记
	printf("%d ",nBegin);
	pMark[nBegin-1] = 1;

	int i;
	//遍历与当前顶点相关的顶点
	for(i = 0;i<pGraph->nVertex;i++)
	{
		//相关的 且未被打印过的
		if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex + i] == 1 
			&& pMark[i] == 0)
		{
			//处理当前节点
			MyDFS(pGraph,i+1,pMark);
		}
	}
}
	

void DFS(Graph *pGraph,int nBegin)
{
	//申请标记数组
	int *pMark = NULL;
	pMark = (int*)malloc(sizeof(int)*pGraph->nVertex);
	memset(pMark,0,sizeof(int)*pGraph->nVertex);

	MyDFS(pGraph,nBegin,pMark);
}



int main()
{
	Graph *pGraph = NULL;
	pGraph = CreateGraph();

	DFS(pGraph,3);		
	return 0;
}
