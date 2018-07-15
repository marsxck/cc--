#include<iostream>
#include<stack>
using namespace std;
template<typename T>
class queue {
public:
	void Push(T value)
	{
		sPush.push(value);
	}
	T Pop()
	{
		while (!sPush.empty())
		{
			sPop.push(sPush.top());
			sPush.pop();
		}
		if (sPop.empty())
		{
			//throw new exception("queue is empty");
			return NULL;
		}			
		T temp = sPop.top();
		sPop.pop();
		return temp;
	}
private:
	stack<T> sPush;
	stack<T> sPop;
};
int main(int argc,char* argv[])
{
	queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	cout << q.Pop() << " ";
	cout << q.Pop() << " ";
	cout << q.Pop() << " ";
	cout << q.Pop() << " ";
}