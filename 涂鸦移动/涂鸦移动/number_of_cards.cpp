#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
#define CARDLENGTH (1.0) //卡片长度
int number_of_cards(float length)
{
	int res=1;
	float a=0.0;//记录长度
	while(length>=a)//当卡片长度大于于累加长度时停止循环
	{
		res+=1;
		a+=CARDLENGTH/res;//累加1/2,1/3,....1/res
	}
	return res-1;//减一得出结果
}
int beauty_of_array(int* a,int nlength)
{
	vector<int> mark;
	//每一个都是子序列，都是美丽值
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
			num+=a[index];//num为a[i]起始的序列的可能美丽值
			auto result=find(mark.begin(),mark.end(),num);
			if(result == mark.end( ))
			{
				mark.push_back(num);
			}
			else
			{
				
				//重复整数，不是美丽值
			}
			index++;
		}

	}
	int res=0;
	for(int i=0;i<mark.size();i++)
	{
		res+=mark[i];//所有美丽值求和
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