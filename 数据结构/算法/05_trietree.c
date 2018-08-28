#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int nFlag;
	struct node *pCharacter[26];
	char *str;
}TrieTree;

void AddWord(TrieTree *pTree,char *str)
{
	int i;
	TrieTree *pTemp = NULL;
	for(i = 0;i<strlen(str);i++)
	{
		//节点的对应位置空 添加节点
		if(pTree->pCharacter[str[i]-97] == NULL)
		{
			pTemp = (TrieTree*)malloc(sizeof(TrieTree));
			memset(pTemp,0,sizeof(TrieTree));

			pTree->pCharacter[str[i]-97] = pTemp;
		}

		//向下走
		pTree = pTree->pCharacter[str[i]-97];
	}

	//末尾标记
	pTree->nFlag++;
	pTree->str = str;
}


TrieTree *CreateTrieTree(char *str[],int nLength)
{
	if(str == NULL || nLength <=0)return NULL;

	TrieTree *pRoot = NULL;
	pRoot = (TrieTree*)malloc(sizeof(TrieTree));
	memset(pRoot,0,sizeof(TrieTree));

	//将字符串依次添加
	int i;
	for(i = 0;i<nLength;i++)
	{
		AddWord(pRoot,str[i]);
	}
	return pRoot;
}

void Search(TrieTree *pRoot,char *str)
{
	if(str == NULL || pRoot == NULL)return;

	int i;
	for(i = 0;i<strlen(str);i++)
	{
		if(pRoot->pCharacter[str[i]-97] == NULL)
		{
			printf("failed.\n");
			return;
		}
		pRoot = pRoot->pCharacter[str[i]-97];
	}
	
	//检测末尾标志
	if(pRoot->nFlag != 0 )
	{
		printf("%s\n",pRoot->str);
		return;
	}
	else
	{
		printf("hhhh failed.\n");
		return;
	}
}

void Traversal(TrieTree *pTree)
{
	if(pTree == NULL)
		return;

	if(pTree->nFlag != 0)
	{
		printf("%s\n",pTree->str);
	}

	int i;
	for(i = 0;i<26;i++)
	{
		Traversal(pTree->pCharacter[i]);
	}
}

int main()
{
	char *str[] = {"app","apple","orange","lemon","logo","ball","tie","glory"};
	TrieTree *pRoot = CreateTrieTree(str,8);
	Traversal(pRoot);
	printf("----------------------\n");
	Search(pRoot,"ball");
	return 0;
}
