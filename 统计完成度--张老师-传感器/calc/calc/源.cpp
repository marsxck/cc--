#include<iostream>
using namespace std;
double dwork;
double dlearn;
double learnself;
double a[50];
void work()
{
	int i;
	printf("输入作业成绩\n");
	cin >> dwork;
	//printf("%.2f\t", dwork*0.1);
	//for (i = 0; i < 2; i++)
	//{
	//	printf("%.2f\t", dwork*0.2);
	//}
	//for (i = 0; i < 5; i++)
	//{
	//	printf("%.2f\t", dwork*0.1);
	//}
	//printf("\n");
	a[0] = dwork*0.1;
	a[6] = a[13] = dwork*0.2;
	a[20] = a[27] = a[34] = a[39] = a[44] = dwork*0.1;
}
void learn()
{
	int i;
	printf("输入学习（讨论）成绩\n");
	cin >> dlearn;
	//printf("%.2f\t", dlearn*0.1);
	//for (i = 0; i < 2; i++)
	//{
	//	printf("%.2f\t", dlearn*0.2);
	//}
	//for (i = 0; i < 5; i++)
	//{
	//	printf("%.2f\t", dlearn*0.1);
	//}
	a[1] = dlearn*0.1;
	a[7] = a[14] = dlearn*0.2;
	a[21] = a[28] = a[35] = a[40] = a[45] = dlearn*0.1;

}
void learns()
{
	int i;
	printf("输入小组（ppt）成绩\n");
	cin >> learnself;
	//for (i = 0; i < 5; i++)
	//{
	//	printf("%.2f\t", learnself*0.1);
	//}
	//for (i = 0; i < 2; i++)
	//{
	//	printf("%.2f\t", learnself*0.2);
	//}
	//printf("%.2f\t", learnself*0.1);
	//printf("\n");
	a[3] = a[9] = a[16] = a[23] = a[30]=a[47] = learnself*0.1;
	a[37] = a[42] = learnself*0.2;
}
void team()
{
	int i;
	double day;
	double dteam;
	printf("输入平时成绩,输出自学\n");
	cin >> day;
	dteam = (day*0.3 - dwork*0.1 - dlearn*0.1 - learnself*0.05) * 20;
	//for (i = 0; i < 5; i++)
	//{
	//	printf("%.2f\t", dteam*0.1);
	//}
	//for (i = 0; i < 2; i++)
	//{
	//	printf("%.2f\t", dteam*0.2);
	//}
	//printf("%.2f\t", learnself*0.1);
	//printf("\n");
	a[2] = a[8] = a[15] = a[22] = a[29] = a[46] = dteam*0.1;
	a[36] = a[41] = dteam*0.2;

}
void middle()
{
	double mi;
	printf("输入期中成绩\n");
	cin >> mi;
	//printf("%.2f\t", a*0.21);
	//printf("%.2f\t", a*0.28);
	//printf("%.2f\t", a*0.18);
	//printf("%.2f\t", a*0.16);
	//printf("%.2f\t", a*0.07);
	//printf("%.2f\t", a*0.1);
	//printf("\n");
	a[4] = mi*0.21;
	a[10] = mi*0.28;
	a[17] = mi *0.18;
	a[24] = mi * 0.16;
	a[31] = mi*0.07;
	a[48] = mi*0.1;
}
void end()
{
	double en;
	printf("输入期末成绩\n");
	cin >> en;
	//printf("%.2f\t", a*0.21);
	//printf("%.2f\t", a*0.28);
	//printf("%.2f\t", a*0.18);
	//printf("%.2f\t", a*0.08);
	//printf("%.2f\t", a*0.05);
	//printf("%.2f\t", a*0.05);
	//printf("%.2f\t", a*0.15);
	//printf("\n");
	a[5] = en*0.21;
	a[11] = en*0.28;
	a[18] = en*0.18;
	a[25] = en * 0.08;
	a[32] = en*0.05;
	a[43] = en*0.05;
	a[49] = en*0.15;
}
void test()
{
	int i;
	double s;
	printf("输入实验成绩\n");
	cin >> s;
	//printf("%.2f\t", a*0.25);
	//printf("%.2f\t", a*0.20);
	//printf("%.2f\t", a*0.20);
	//printf("%.2f\t", a*0.25);
	//printf("%.2f\t", a*0.1);
	//printf("\n");
	a[12] = s*0.25;
	a[19] =a[26]= s*0.2;
	a[33] = s*0.25;
	a[38] = s * 0.1;
}
void main()
{
	int i=1;
	while (1)
	{
		cout << "第" << i << "个"<<endl;
		work();
		learn();
		learns();
		team();
		middle();
		end();
		test();
		i++;
		for (int f = 0; f < 50; f++)
		{
			printf("第%d个数据：%.2f\n", f, a[f]);
		}
		printf("\n");
	}

	return;
}