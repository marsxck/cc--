#include<iostream>
#include<vector>
#include<list>
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
int getres(int a[], int nlength)
{
	//错误处理
	if (a == nullptr || nlength <= 1)
		return -1;
	int i, res = 0;
	int nMax = a[0];
	int nMin = a[0];
	//找到最大值
	for (i = 1; i < nlength; i++)
	{
		if (a[i] > nMax)
			nMax = a[i];
	}
	//申请一个nMax+1大小的数组 0.....nMax
	int *count = (int*)malloc(sizeof(int)*(nMax + 1));
	memset(count,0, sizeof(int)*(nMax + 1));
	//遍历原数组，进行计数
	for (i = 0; i < nlength; i++)
	{
		count[a[i]]++;
		cout << count[a[i]];
	}
		
	//遍历计数数组，计算贴纸数量
	int flag = 0;//用于标记第几高的分数
	for (i = 0; i < nMax + 1; i++)
	{
		if (count[i] > 0)
		{
			flag++;//最小为1，依次递增
			while (count[i]-- != 0)//累加同分的小孩
			{
				res += flag;
			}
		}
	}
	return res;
}


void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
	if (pStr == NULL)
		return;

	Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin)
{
	if (*pBegin == '\0')
	{
		printf("%s\n", pStr);
	}
	else
	{
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
		{
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);

			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}
void swap(string &str, int start, int begin)
{
	char temp = str[start];
	str[start] = str[begin];
	str[begin] = temp;
}
void core(string &str, int begin, vector<string> &res)
{
	if (*(str.c_str() + begin) == '\0')
	{
		res.push_back(str);
		return;
	}

	for (int start = begin; str[start] != '\0'; start++)
	{
		if (start != begin&&str[start] == str[begin])
			continue;
		swap(str, begin, start);
		core(str, begin + 1, res);
		swap(str, begin, start);
	}
}
vector<string> Permutation(string str) {
	//递归？
	vector<string> res;
	if (str.c_str() == NULL) return res;
	core(str, 0, res);
	return res;
}
void adjust(int root, int length, vector<int> &arr)
{
	for (int max = 2 * root + 1; max <= length - 1; max = 2 * root + 1)
	{
		//如果有右孩子
		if (max + 1 <= length)
		{
			//比较左右孩子大小
			if (arr[max + 1]>arr[max])
				max = max + 1;
		}
		//和根节点比较
		if (arr[root]<arr[max])
		{
			int temp = arr[root];
			arr[root] = arr[max];
			arr[max] = temp;
			root = max;
		}
		else
		{
			break;
		}
	}
}
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	//建大堆大小为k,根节点0-k/2-1
	vector<int> res;
	if (input.empty() || k<1)
		return res;
	for (int i = k / 2 - 1; i >= 0; i--)
	{
		adjust(i, k, input);
	}
	for (int i = k; i<input.size(); i++)
	{
		if (input[i]<input[0])
		{
			input[0] = input[i];
			adjust(0, k, input);
		}
	}
	for (int i = 0; i<k; i++)
	{
		res.push_back(input[i]);
	}
	return res;
}
void Reverse(string&str, int start, int end)
{
	char temp;
	while (start<end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
string ReverseSentence(string str) {
	//找到空格
	if (str.length() == 0)
		return str;
	int index = 0;
	vector<int> pos;
	while (index<str.length())
	{
		if (str[index] == ' ')
			pos.push_back(index);
		index++;
	}
	if (pos.size() == 0)
	{
		return str;
	}
	//翻转每个单词
	int start = 0;
	int end = 0;
	for (int i = 0; i<pos.size() - 1; i++)
	{
		end = pos[i] - 1;
		Reverse(str, start, end);
		start = pos[i] + 1;
	}
	//翻转最后一个单词
	Reverse(str, start, str.length() - 1);
	Reverse(str, 0, str.length() - 1);
	return str;
}
int LastRemaining_Solution(int n, int m)
{
	//链表储存
	if (n<1)
		return 0;
	list<int> ls;
	for (int i = 0; i<n; i++)
	{
		ls.push_back(i);
	}
	//模拟环形链表
	auto ite = ls.begin();
	while (ls.size() != 1)
	{
		for (int i = 1; i<m; i++)
		{
			ite++;
			if (ite == ls.end())
				ite = ls.begin();
		}
		ite = ls.erase(ite);
		if (ite == ls.end())
			ite = ls.begin();
	}
	return ls.front();
}
int res = 0;
int counte = 1;
class Add {
public:
	Add()
	{
		res += counte;
		counte++;
	}
};
int Sum_Solution(int n) {
	Add* p = new Add[n];
	delete[]p;
	return res;
}
int main()
{
	Sum_Solution(5);


}