#include "Rocket.h"



CRocket::CRocket()
{
	m_hBmp_JumpItem = 0;
	x = 0;
	y = 0;
}


CRocket::~CRocket()
{
	DeleteObject(m_hBmp_JumpItem);
	m_hBmp_JumpItem = 0;
}

bool CRocket::IsTouchPlayer(CPlayer& player)
{
	//ÎïÌå×ø±ê(x,y)(x,y+36)(x+25,y)(x+25,y+36)
	if (x >= player.x&&x <= player.x + 53 && y >= player.y&&y <= player.y + 52 ||
		x >= player.x&&x <= player.x + 53 && y + 36 >= player.y&&y + 36 <= player.y + 52 ||
		x + 25 >= player.x&&x + 25 <= player.x + 53 && y + 36 >= player.y&&y + 36 <= player.y + 52)
		return true;
	return false;
}
bool CRocket::ItemJump(CPlayer& player)
{
	return true;
}
void CRocket::InitItem(HINSTANCE hIns)
{
	m_hBmp_JumpItem = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ROCKET));
}
void CRocket::JumpItemShow(HDC hdctemp)
{
	HDC hdc = CreateCompatibleDC(hdctemp);
	SelectObject(hdc, m_hBmp_JumpItem);
	BitBlt(hdctemp, x, y, 25, 36, hdc, 0, 0, SRCAND);
	DeleteDC(hdc);
}