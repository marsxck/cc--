#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *GetNext(char *str)
{
	int *pNext = NULL;
	pNext = (int *)malloc(sizeof(int)*256);
	memset(pNext,-1,sizeof(int)*256);

	//从右向左第一次出现的下标
	int i = 0;
	for(i = 0;i<strlen(str);i++)
	{
		pNext[str[i]] = i;
	}
	return pNext;
}

int Sunday(char *src,char *match)
{
	if(src == NULL || match == NULL)return -1;


	//获得next数组
	int *pNext = NULL;
	pNext = GetNext(match);

	int i; //遍历主串
	int j; //遍历匹配串的
	int k; //对应的开头的位置

	i = 0;
	j = 0;

	while(i < strlen(src) && j < strlen(match))
	{
		k  = i;
		while(src[i] == match[j])
		{
			i++;
			j++;
		}
		if(j == strlen(match))
		{
			return i-j;
		}
		else
		{
			//找到主串对应匹配串的下一位置
			//找到当前字符在匹配串中第一次出现的下标
			i = k+strlen(match) - pNext[src[k+strlen(match)]];
			j = 0;
		}
	}
	return -1;
}

int main()
{
	int n;
	n = Sunday("abcabcdabcabceabcabcdabcabcadshfoiewr","abcabcdabcabca");
	printf("%d\n",n);
	return 0;
}
