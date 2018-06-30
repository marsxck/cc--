#include "BlackHole.h"



CBlackHole::CBlackHole()
{
	m_hBmp_JumpItem = 0;
	x = 0;
	y = 0;
}


CBlackHole::~CBlackHole()
{
	DeleteObject(m_hBmp_JumpItem);
}
bool CBlackHole::IsTouchPlayer(CPlayer& player)
{
	if ((x + 72 >= player.x && player.x >= x && y <= player.y && player.y <= y + 72)
		|| (x + 72 >= player.x + 53 && player.x + 53 >= x && y <= player.y && player.y <= y + 72 )
		|| (x + 72 >= player.x && player.x >= x && y <= player.y + 52 && player.y + 52 <= y + 72 )
		|| (x + 72 >= player.x + 53 && player.x + 53 >= x && y <= player.y + 52 && player.y + 52 <= y + 72 )
		|| (x + 72 >= player.x && player.x >= x && y <= player.y + 30 && player.y + 30 <= y + 72 )
		|| (x + 72 >= player.x + 30 && player.x + 30 >= x && y <= player.y && player.y <= y + 72 )
		|| (x + 72 >= player.x + 30 && player.x + 30 >= x && y <= player.y + 52 && player.y + 52 <= y + 72 )
		|| (x + 72 >= player.x + 53 && player.x + 53 >= x && y <= player.y + 30 && player.y + 30 <= y + 72 ))
	{
		return true;
	}

	return false;
}
bool CBlackHole::ItemJump(CPlayer& player)
{
	return true;
}
void CBlackHole::InitItem(HINSTANCE hIns)
{
	m_hBmp_JumpItem = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_Black_Hole));
}
void CBlackHole::JumpItemShow(HDC hdctemp)
{
	HDC hdc = CreateCompatibleDC(hdctemp);
	SelectObject(hdc, m_hBmp_JumpItem);
	BitBlt(hdctemp, x, y, 80, 55, hdc, 0, 0, SRCAND);
	DeleteDC(hdc);
}
