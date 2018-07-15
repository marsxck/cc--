#include<iostream>
using namespace std;
void ReplaceBlank(char str[],int nLength)
{
	//校验参数
	if (str == NULL || nLength <= 0)
		return;
	//计算新字符串长度，空格个数
	int i = 0;
	int nBlankNum = 0;
	int nLen = 0;
	int nNewLen = 0;
	while (str[i]!='\0')
	{
		nLen++;
		if (str[i] == ' ')
			nBlankNum++;
		i++;
	}
	nNewLen = nBlankNum * 2 + nLen;
	if (nNewLen > nLength)
		return;
	//替换
	while (nLen > 0&&nNewLen>0)
	{
		if (str[nLen] == ' ')
		{
			str[nNewLen--] = '0';
			str[nNewLen--] = '2';
			str[nNewLen--] = '%';
		}
		else
		{
			str[nNewLen--] = str[nLen];
		}
		nLen--;
	}
}
void main()
{
	char a[20] = "hello wo";
	ReplaceBlank(a, 20);
	cout << a << endl;
}