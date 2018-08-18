#include<iostream>
#include<vector>
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
	//������
	if (a == nullptr || nlength <= 1)
		return -1;
	int i, res = 0;
	int nMax = a[0];
	int nMin = a[0];
	//�ҵ����ֵ
	for (i = 1; i < nlength; i++)
	{
		if (a[i] > nMax)
			nMax = a[i];
	}
	//����һ��nMax+1��С������ 0.....nMax
	int *count = (int*)malloc(sizeof(int)*(nMax + 1));
	memset(count,0, sizeof(int)*(nMax + 1));
	//����ԭ���飬���м���
	for (i = 0; i < nlength; i++)
	{
		count[a[i]]++;
		cout << count[a[i]];
	}
		
	//�����������飬������ֽ����
	int flag = 0;//���ڱ�ǵڼ��ߵķ���
	for (i = 0; i < nMax + 1; i++)
	{
		if (count[i] > 0)
		{
			flag++;//��СΪ1�����ε���
			while (count[i]-- != 0)//�ۼ�ͬ�ֵ�С��
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
	//�ݹ飿
	vector<string> res;
	if (str.c_str() == NULL) return res;
	core(str, 0, res);
	return res;
}
void adjust(int root, int length, vector<int> &arr)
{
	for (int max = 2 * root + 1; max <= length - 1; max = 2 * root + 1)
	{
		//������Һ���
		if (max + 1 <= length)
		{
			//�Ƚ����Һ��Ӵ�С
			if (arr[max + 1]>arr[max])
				max = max + 1;
		}
		//�͸��ڵ�Ƚ�
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
	//����Ѵ�СΪk,���ڵ�0-k/2-1
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
int main()
{
	vector<int> arr = { 4,5,1,6,2,7,3,8 };
	
	vector<int> res= GetLeastNumbers_Solution(arr, 4);

}