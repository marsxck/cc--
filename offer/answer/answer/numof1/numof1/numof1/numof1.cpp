#include<iostream>
using namespace std;
int numof1(int num)
{
	int count = 0;
	while (num)
	{
		count++;
		num = (num - 1)&num;
	}
	return count;
}
void main()
{
	cout << numof1(9) << endl;

}