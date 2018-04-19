#include<iostream>
using namespace std;
typedef struct info {
	int max;
	int begin;
	int end;
	info()
	{
		max = 0;
		begin = 0;
		end = 0;
	}
}INFO;
class opt
{
protected:
	opt() {}
private:
	static opt* instance;
public:
	int begin=0;
	int end=0;
	int max=0;
	static opt* GetOpt()
	{
		if (instance == nullptr)
		{
			instance = new opt();
		}
		return instance;
	}
	INFO find(int* arr, int from, int to)
	{
		INFO info;
		if (from == to)
		{
			info.max = arr[from];
			info.begin = from;
			info.end = from;
			return info;
		}
			
		int middle = (from + to) / 2;
		INFO m1 = find(arr, from, middle);
		INFO m2 = find(arr,middle + 1, to);
		int left = arr[middle];
		int ml = arr[middle];
		info.begin = middle;
		for (int i = middle - 1; i >= from; i--)
		{
			ml = ml + arr[i];
			if (ml > left)
			{
				left = ml;
				info.begin = i;
			}
		}
		int right = arr[middle+1];
		int mr = arr[middle+1];
		info.end = middle + 1;
		for (int i = middle + 2; i <= to; i++)
		{
			mr = mr + arr[i];
			if (mr > right)
			{
				right = mr;
				info.end = i;
			}
		}
		info.max = right + left;
		if (m1.max >= m2.max&&m1.max >= info.max)
		{
			max = m1.max;
			begin = m1.begin;
			end = m1.end;
			return m1;
		}
		if (m2.max >= m1.max&&m2.max >=info.max)
		{
			max = m2.max;
			begin = m2.begin;
			end = m2.end;
			return m2;
		}
		if (info.max >= m2.max&&info.max >= m1.max)
		{
			max = info.max;
			begin = info.begin;
			end = info.end;
			return info;
		}
	}
	

};
opt* opt::instance = nullptr;
int main()
{
	opt* p = opt::GetOpt();
	int arr[] = { 1,-2,3,10,-4,7,2,-5 };
	p->find(arr, 0, 7);
	cout << p->max<<""<<p->begin<<""<<p->end<<"" << endl;

}