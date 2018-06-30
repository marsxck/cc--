#pragma once
#include"sys.h"
#include"Player.h"
#include"GameTable.h"
class CBack
{
private:
	HBITMAP HB_Back_One;
	HBITMAP HB_Back_Two;
	HBITMAP HB_Back_Three;
	HBITMAP HB_Back_Four;
	int Back_x;
	int Back_y;
	int playerpos;
	
public:
	CBack();
	~CBack();
	void InitBack(HINSTANCE hIns);
	void BackShow(HDC hdc);
	void Back2Show(HDC hdc);
	void FisBack(CPlayer& player);//Ë¢ÐÂ±³¾°

};

