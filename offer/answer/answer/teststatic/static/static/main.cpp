#include<iostream>
using namespace std;
class test {
public:
	void show() {
		cout << "llll" << endl;
	}
};
void main()
{
	test* p = NULL;
	p->show();

}
