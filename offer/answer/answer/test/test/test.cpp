#include<iostream>
using namespace std;
class Singleton {
	Singleton()
	{
		cout << "struct" << endl;
	}
public:
	static Singleton* getinstance()
	{
		static Singleton* instance = new Singleton;
		return instance;
	}
};
int main()
{
	Singleton* p= Singleton::getinstance();
	Singleton* p1 = Singleton::getinstance();
}