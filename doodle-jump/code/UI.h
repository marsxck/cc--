#pragma once
#include"sys.h"
class CUI
{
public:
	CUI();
	~CUI();
public:
	int x;
	int y;
	HBITMAP m_bitmap;
public:
	void InitBack(HINSTANCE hIns);
	void BackShow(HDC hdc);
};

