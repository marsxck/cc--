#include "UI2.h"

CUI2::CUI2()
{
	m_bitmap = 0;
	x = 0;
	y = 0;
}


CUI2::~CUI2()
{
	DeleteObject(m_bitmap);
}
void CUI2::InitBack(HINSTANCE hIns)
{
	m_bitmap = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_UI2));
}
void CUI2::BackShow(HDC hdc)
{
	HDC hdctemp = CreateCompatibleDC(hdc);


	SelectObject(hdctemp, m_bitmap);
	BitBlt(hdc, x, y, 380, 550, hdctemp, 0, 0, SRCCOPY);

	DeleteDC(hdctemp);
}


