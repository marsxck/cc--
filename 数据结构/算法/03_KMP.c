#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *GetNext(char *str)
{
	int n;
	n = strlen(str);

	int *pNext = NULL;
	pNext = (int*)malloc(sizeof(int)*n);

	pNext[0] = 0;

	int i = 1;
	int j = i-1;
	while(i < n)
	{
		if(str[i] == str[pNext[j]])
		{
			pNext[i] = pNext[j]+1;
			i++;
			j = i-1;
		}
		else if(pNext[j] == 0)
		{
			pNext[i] = 0;
			i++;
			j = i-1;
		}
		else
		{
			j = pNext[j]-1;
		}
	}
	return pNext;
}


int KMP(char *src,char *match)
{
	if(src == NULL || match == NULL)return -1;

	//获得next数组
	int *pNext = NULL;
	pNext = GetNext(match);

	//匹配
	int i;
	int j;
	i = 0;
	j = 0;

	while(i < strlen(src) && j < strlen(match))
	{
		//二者相等  一起向后移动
		if(src[i] == match[j])
		{
			i++;
			j++;
		}
		else
		{
			//不想等 且匹配串已经走到头的位置 
			if(j == 0)
			{
				//主串向后移动
				i++;
			}
			else
			{
				//跳转
				j = pNext[j-1];
			}
		}
	}

	//匹配串走到末尾 查找成功
	if(j == strlen(match))
	{

		return i - j;
	}
	return -1;
}

int main()
{
	int n;
	n = KMP("abcabcdabcabceabcabcdabcabcadshfoiewr","abcabcdabcdsnhfrewroiabca");
	printf("%d\n",n);
	return 0;
}
