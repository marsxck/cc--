#pragma once
#include"sys.h"
#include<map>
class CScore
{
public:
	CScore();
	~CScore();
public:
	void InitScore(HINSTANCE hIns);
	void ShowScore(HDC hdcmen,int Score);
	void ShowScore(HDC hdcmen, int Score,int x,int y);
private:
	map<int, HBITMAP> m_MapNumToBit;
};

