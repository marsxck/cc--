#include<iostream>
using namespace std;
int abctoint(char* str)
{
	if (str == NULL)
		throw "error";
	int nCount = 0;
	char* temp = str;
	while (*temp != '\0')
	{
		temp++;
		nCount++;
	}
	int n = 1;
	for (int i = 1; i < nCount; i++)
	{
		n *= 26;
	}
	int res = 0;
	for (n; n >= 1; n /= 26)
	{
		res += (*str - 'A'+1)*n;
		str++;
	}
	return res;
}
void main()
{
	int a=abctoint("A");
 }