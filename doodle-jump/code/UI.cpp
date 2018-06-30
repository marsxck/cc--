#include "UI.h"

CUI::CUI()
{
	m_bitmap = 0;
	x = 0;
	y = 0;
}


CUI::~CUI()
{
	DeleteObject(m_bitmap);
}
void CUI::InitBack(HINSTANCE hIns)
{
	m_bitmap = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_UI));
}
void CUI::BackShow(HDC hdc)
{
	HDC hdctemp = CreateCompatibleDC(hdc);


	SelectObject(hdctemp, m_bitmap);
	BitBlt(hdc, x, y, 380, 550, hdctemp, 0, 0, SRCCOPY);

	DeleteDC(hdctemp);
}

