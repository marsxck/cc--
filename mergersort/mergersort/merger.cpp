#include<iostream>
//ºÏ²¢low-mid mid+1-high
void merger(int arr[],int low,int high)
{
	if (arr == NULL || low == high)
		return;
	int mid = (low + high) / 2;
	//1  low~~mid
	//2  mid+1~~high
	int* temp = (int*)malloc(sizeof(int)*(high - low + 1));
	int nBegin1 = low, nEnd1 = mid, nBegin2 = mid + 1, nEnd2 = high,count=0;
	while (nBegin1<=nEnd1&&nBegin2<=nEnd2)
	{
		if (arr[nBegin1] > arr[nBegin2])
		{
			temp[count] = arr[nBegin1];
			nBegin1++;
		}
		else
		{
			temp[count] = arr[nBegin2];
			nBegin2++;
		}
		count++;
	}
	while (nBegin1 <= nEnd1)
	{
		temp[count++] = arr[nBegin1++];
	}
	while (nBegin2 <= nEnd2)
	{
		temp[count++] = arr[nBegin2++];
	}
	for (int i=count-1;i>=0;i--)
	{
		arr[high--] = temp[i];
	}
	free(temp);
}
void mergersort(int arr[],int low,int high)
{
	if (low >= high || arr == NULL)
		return;
	int mid = (low + high) / 2;
	mergersort(arr, low, mid);
	mergersort(arr, mid + 1, high);
	merger(arr,low,high);
}
int fun(int a[], int b, int e)
{
	if (e - b <= 1)
		return abs(a[b] -a[e]) >= 3 ? a[b] : a[e];
	int l = 0, r = 0;
	l = fun(a, b, b + (e - b) / 2);
	if (l % 2 == 0)
		r = fun(a, b + (e - b) / 2 + 1, e);
	else
		return 1;
	if (1 | r)
		return 1 | r;
	else
		return r;
}
int main()
{
	int a[] = { 10,5,8,4,5,20,2,3 };
	std::cout << fun(a, 0, 8);
	//mergersort(a,0,3);
	return 0;
}