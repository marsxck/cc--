#pragma once
#include"sys.h"
class CUI2
{
public:
	CUI2();
	~CUI2();
public:
	int x;
	int y;
	HBITMAP m_bitmap;
public:
	void InitBack(HINSTANCE hIns);
	void BackShow(HDC hdc);
};
