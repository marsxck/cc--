#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
#define CARDLENGTH (1.0) //��Ƭ����
int number_of_cards(float length)
{
	int res=1;
	float a=0.0;//��¼����
	while(length>=a)//����Ƭ���ȴ������ۼӳ���ʱֹͣѭ��
	{
		res+=1;
		a+=CARDLENGTH/res;//�ۼ�1/2,1/3,....1/res
	}
	return res-1;//��һ�ó����
}
int beauty_of_array(int* a,int nlength)
{
	vector<int> mark;
	//ÿһ�����������У���������ֵ
	for(int i=0;i<nlength;i++)
	{
		mark.push_back(a[i]);
	}
	for(int i=0;i<nlength;i++)
	{
		int index=i+1;
		int num=a[i];
		while(index<=nlength-1)
		{
			num+=a[index];//numΪa[i]��ʼ�����еĿ�������ֵ
			auto result=find(mark.begin(),mark.end(),num);
			if(result == mark.end( ))
			{
				mark.push_back(num);
			}
			else
			{
				
				//�ظ���������������ֵ
			}
			index++;
		}

	}
	int res=0;
	for(int i=0;i<mark.size();i++)
	{
		res+=mark[i];//��������ֵ���
	}
	return res;
}
int main()
{
	//float res=0.0;
	//for(int i=0;i<60;i++)
	//{
	//	res+=CARDLENGTH/(i+2);
	//}
	//cout<<res;
	int a[]={1};
	int b[]={1,2};
	int c[]={1,1,2};
	cout<<beauty_of_array(a,1);
	cout<<beauty_of_array(b,2);
	cout<<beauty_of_array(c,3);
}