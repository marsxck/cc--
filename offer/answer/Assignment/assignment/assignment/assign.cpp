#include"assign.h"
MyString::MyString(char* pStr = nullptr)
{
	if (pStr == nullptr)
	{
		m_pStr = new char[1];
		m_pStr[0] = '\0';
	}
	else
	{
		int nLength = strlen(pStr);
		m_pStr = new char[nLength + 1];
		strcpy_s(m_pStr, nLength + 1, pStr);
	}
}
//MyString(const MyString &str);
MyString::~MyString()
{
	delete[]m_pStr;
	m_pStr = nullptr;
}
MyString& MyString::operator=(const MyString&str)
{
	if (this != &str)
	{
		int nLength = strlen(str.m_pStr);
		char* pTemp = new char[nLength + 1];
		strcpy_s(pTemp, nLength + 1, str.m_pStr);
		delete[]m_pStr;
		m_pStr = pTemp;
		pTemp = nullptr;
	}
	return *this;
}
MyString& MyString::operator=(const char* const str)
{
	if (str!=nullptr)
	{
		int nLength = strlen(str);
		char* pTemp = new char[nLength + 1];
		strcpy_s(pTemp, nLength + 1, str);
		delete[]m_pStr;
		m_pStr = pTemp;
		pTemp = nullptr;
	}
	return *this;
}
void MyString::show()
{
	cout << this->m_pStr << endl;
}
