#include "Score.h"



CScore::CScore()
{

}


CScore::~CScore()
{
	for (int i = 0; i < 10; i++)
	{
		DeleteObject(m_MapNumToBit[i]);
		m_MapNumToBit[i] = 0;
	}
}
void CScore::InitScore(HINSTANCE hIns)
{
	for (int i = 0; i < 10; i++)
	{
		m_MapNumToBit[i] = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BITMAP4+i));
	}

	
}
void CScore::ShowScore(HDC hdcmen, int Score)
{
	HDC hdctemp = CreateCompatibleDC(hdcmen);
	int i = 1000000;
	int x=0, y=0;
	for (int i = 1000000;i>=1;i/=10)
	{
		
		SelectObject(hdctemp,m_MapNumToBit[Score/i%10]);
		BitBlt(hdcmen, x, y, 20, 24, hdctemp, 0, 0, SRCAND);
	
		x += 20;
	}
	DeleteDC(hdctemp);

}
void CScore::ShowScore(HDC hdcmen, int Score, int x, int y)
{
	HDC hdctemp = CreateCompatibleDC(hdcmen);
	int i = 1000000;
	for (int i = 1000000;i >= 1;i /= 10)
	{

		SelectObject(hdctemp, m_MapNumToBit[Score / i % 10]);
		BitBlt(hdcmen, x, y, 20, 24, hdctemp, 0, 0, SRCAND);

		x += 20;
	}
	DeleteDC(hdctemp);
}