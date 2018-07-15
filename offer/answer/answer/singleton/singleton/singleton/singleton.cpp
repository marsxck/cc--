// singleton.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
class single1 {
private:
	single1()
	{
		cout << "creat obj" << endl;
	}
public:
	
	static single1& GetInstance()
	{
		return *sin::p;
	}
	class sin 
	{
	public:
		static single1* p;
	};
	
};
single1* single1::sin::p = new single1;

int main()
{
	single1 a = single1::GetInstance();
	single1 b = single1::GetInstance();

    return 0;
}

