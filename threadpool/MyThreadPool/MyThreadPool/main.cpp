#include <iostream>
#include "MyThreadPool.h"
using namespace std;


class AddItask :public Itask
{
public:
	 AddItask(int a,int b):m_a(a),m_b(b)
	{}
	virtual~AddItask()
	{}
public:
	void RunItask()
	{
		cout<<m_a <<"+"<<m_b <<"="<<m_a+m_b<<endl;
	}
private:
	int m_a;
	int m_b;
};


int main()
{
	CMyThreadPool tp;
	tp.CreateThreadPool(11,20);
	system("pause");
	tp.DestroyThreadPool();
	//for(int i = 0; i <20000;i++)
	//{
	//	Itask *p = new AddItask(i,i+1);
	//	tp.PushItask(p);
	//}

	while (1);
	
	return 0;
}