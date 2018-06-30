#include "Back.h"
#include"JumpApp.h"


CBack::CBack()
{
	HB_Back_One = 0;
	HB_Back_Two = 0;
	HB_Back_Three = 0;
	HB_Back_Four = 0;
	Back_x = 0;
	Back_y = 0;

}


CBack::~CBack()
{
	DeleteObject(HB_Back_One);
	DeleteObject(HB_Back_Two);
	HB_Back_One = 0;
	HB_Back_Two = 0;
	DeleteObject(HB_Back_Three);
	DeleteObject(HB_Back_Four);
	HB_Back_Three = 0;
	HB_Back_Four = 0;
}
void CBack::InitBack(HINSTANCE hIns)
{

	HB_Back_One = LoadBitmap(hIns,MAKEINTRESOURCE(ID_HB_Back_One));
	HB_Back_Two= LoadBitmap(hIns, MAKEINTRESOURCE(ID_HB_Back_One));
	HB_Back_Three = LoadBitmap(hIns, MAKEINTRESOURCE(ID_HB_Back_Two));
	HB_Back_Four = LoadBitmap(hIns, MAKEINTRESOURCE(ID_HB_Back_Two));

}
void CBack::BackShow(HDC hdc)
{
	HDC hdctemp = CreateCompatibleDC(hdc);

	SelectObject(hdctemp, HB_Back_Two);
	BitBlt(hdc, Back_x, Back_y-550, 380, 550, hdctemp, 0, 0, SRCCOPY);



	SelectObject(hdctemp,HB_Back_One);
	BitBlt(hdc,Back_x,Back_y,380,550,hdctemp,0,0,SRCCOPY);


	DeleteDC(hdctemp);
}
void CBack::Back2Show(HDC hdc)
{
	HDC hdctemp = CreateCompatibleDC(hdc);

	SelectObject(hdctemp, HB_Back_Three);
	BitBlt(hdc, Back_x, Back_y - 550, 380, 550, hdctemp, 0, 0, SRCCOPY);



	SelectObject(hdctemp, HB_Back_Four);
	BitBlt(hdc, Back_x, Back_y, 380, 530, hdctemp, 0, 20, SRCCOPY);


	DeleteDC(hdctemp);
}
void CBack::FisBack(CPlayer& player)
{
	if (Back_y ==550)
	{
		Back_y = 0;
	}
	else
	{
		if (1)
		{
			Back_y+=10;
		}
		
	}

}