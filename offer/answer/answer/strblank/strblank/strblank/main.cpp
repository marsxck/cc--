#include<iostream>
using namespace std;
void ReplaceBlank(char str[],int nLength)
{
	//У�����
	if (str == NULL || nLength <= 0)
		return;
	//�������ַ������ȣ��ո����
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
	//�滻
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