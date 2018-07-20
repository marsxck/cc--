#include<iostream>
using namespace std;
template <class T>
class Cmyp {
private:
	T* m_p;
public:
	Cmyp(T* p):m_p(p)
	{
	
	}
	~Cmyp()
	{
		delete m_p;
	}
	T* operator->()
	{
		return m_p;
	}
	void print()
	{
	
	}
};
class CTest {
public:
	CTest() :m_n(0)
	{
	
	}
	void show()
	{
		cout << m_n << endl;
	}
private:
	int m_n;

};
void main()
{
	Cmyp<CTest> p(new CTest);
	p->show();

}