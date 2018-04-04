#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int main()
{
	char buff[6];
	cin >> buff;
	char* p = buff;
	char strh[3];
	char strm[3];
	int i = 0;
	int j = 0;
	while (*p != '\0')
	{
		if (*p == ':')
		{
			p++;
			while (*p != '\0')
			{
				strm[j] = *p;
				j++;
				p++;
			}
			break;
		}
		strh[i] = *p;
		i++;
		p++;
	}
	strh[i] = '\0';
	strm[j] = '\0';
	float nh, nm;
	float rh, rm;
	nh = (float)atoi(strh);
	nm = (float)atoi(strm);
	if (nh < 0 || nh>23 || nm < 0 || nm>59)
		return 0;
	if (nh>12)
		nh = 24 - nh;
	rh = nh / 12 * 360 + nm / 60 * 30;
	rm = nm / 60 * 360;
	float res;
	res = rm - rh;
	if (res<0)
		res = -res;//ÇóÁÓ½Ç
	if (res > 180)
		res = 360 - res;
	if (int(res) == res)
		cout << (int)res << endl;
	else
		printf("%.1f\n", res);
	system("pause");

}