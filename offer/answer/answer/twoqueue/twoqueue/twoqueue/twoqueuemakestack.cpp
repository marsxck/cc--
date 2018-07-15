#include<iostream>
#include<queue>
using namespace std;
template<typename T>
class MyStack
{
public:
	void push(T value)
	{
		if (q1.empty())
		{
			q2.push(value);
			return;
		}
		q1.push(value);
	}
	T pop()
	{
		if (q1.empty() && q2.empty())
		{
			cout << "stack empty" << endl;
			return -1;
		}
		T temp = NULL;
		if (q1.empty())
		{
			while (q2.size() != 1)
			{
				q1.push(q2.front());
				q2.pop();
			}
			temp = q2.front();
			q2.pop();
			return temp;
		}
		if (q2.empty())
		{
			while (q1.size() != 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			temp = q1.front();
			q1.pop();
			return temp;
		}
	}
private:
	queue<T> q1;
	queue<T> q2;
};
void main()
{
	MyStack<int> mys;
	mys.push(1);
	mys.push(2);
	mys.push(3);
	mys.push(4);
	cout << mys.pop() << " ";
	cout << mys.pop() << " ";
	cout << mys.pop() << " ";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	cout << mys.pop() << " ";
                                                                                                                                                        	cout << mys.pop() << " ";
}