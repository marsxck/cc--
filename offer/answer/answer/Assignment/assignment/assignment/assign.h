#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;
class MyString
{
private:
	char* m_pStr;
public:
	MyString();
	MyString(char* pStr);
	MyString(const MyString &str);
	~MyString();
	MyString& operator=(const MyString&str);
	MyString& operator=(const char* const str);
	void show();
};