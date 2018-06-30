#include "Monster2.h"



CMonster2::CMonster2()
{
	m_hBmp_JumpItem = 0;
	x = 0;
	y = 0;
}


CMonster2::~CMonster2()
{
	DeleteObject(m_hBmp_JumpItem);
}
bool CMonster2::IsTouchPlayer(CPlayer& player)
{
	if ((x + 80 >= player.x && player.x >= x && y <= player.y && player.y <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x + 53 && player.x + 53 >= x && y <= player.y && player.y <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x && player.x >= x && y <= player.y + 52 && player.y + 52 <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x + 53 && player.x + 53 >= x && y <= player.y + 52 && player.y + 52 <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x && player.x >= x && y <= player.y + 30 && player.y + 30 <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x + 30 && player.x + 30 >= x && y <= player.y && player.y <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x + 30 && player.x + 30 >= x && y <= player.y + 52 && player.y + 52 <= y + 55 && player.m_nJump_Flag == JUMPUP)
		|| (x + 80 >= player.x + 53 && player.x + 53 >= x && y <= player.y + 30 && player.y + 30 <= y + 55 && player.m_nJump_Flag == JUMPUP))
	{
		return true;
	}

	return false;
}
bool CMonster2::ItemJump(CPlayer& player)
{
	if ((player.x >= x && player.x <= x + 80 && player.y + 52>y - 55 && player.y + 52<y && player.m_nJump_Flag == JUMPDOWN)
		|| (player.x + 25 >= x && player.x + 25 <= x + 80 && player.y + 52>y - 55 && player.y + 52<y && player.m_nJump_Flag == JUMPDOWN)
		|| (player.x + 53 >= x && player.x + 53 <= x + 80 && player.y + 52>y - 55 && player.y + 52<y && player.m_nJump_Flag == JUMPDOWN))
	{
		return true;
	}
	return false;
}
void CMonster2::InitItem(HINSTANCE hIns)
{
	m_hBmp_JumpItem = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_Monster2));
}
void CMonster2::JumpItemShow(HDC hdctemp)
{
	HDC hdc = CreateCompatibleDC(hdctemp);
	SelectObject(hdc, m_hBmp_JumpItem);
	BitBlt(hdctemp, x, y, 80, 55, hdc, 0, 0, SRCAND);
	DeleteDC(hdc);
}


