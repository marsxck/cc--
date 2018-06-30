#include "Monster.h"



CMonster::CMonster()
{
	m_hBmp_JumpItem = 0;
	x = 0;
	y = 0;
}


CMonster::~CMonster()
{
	DeleteObject(m_hBmp_JumpItem);
}
bool CMonster::IsTouchPlayer(CPlayer& player)
{
	if ((x + 40 >= player.x && player.x >= x && y <= player.y && player.y <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x + 53 && player.x + 53 >= x && y <= player.y && player.y <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x && player.x >= x && y <= player.y + 52 && player.y + 52 <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x + 53 && player.x + 53 >= x && y <= player.y + 52 && player.y + 52 <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x && player.x >= x && y <= player.y + 30 && player.y + 30 <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x + 30 && player.x + 30 >= x && y <= player.y && player.y <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x + 30 && player.x + 30 >= x && y <= player.y + 52 && player.y + 52 <= y + 45 && player.m_nJump_Flag == JUMPUP)
		|| (x + 40 >= player.x + 53 && player.x + 53 >= x && y <= player.y + 30 && player.y + 30 <= y + 45 && player.m_nJump_Flag == JUMPUP))
	{
		return true;
	}

	return false;
}
bool CMonster::ItemJump(CPlayer& player)
{
	if ((player.x >= x && player.x <= x + 40 && player.y + 52>y - 45 && player.y + 52<y && player.m_nJump_Flag == JUMPDOWN)
		|| (player.x + 25 >= x && player.x + 25 <= x + 40 && player.y + 52>y - 45 && player.y + 52<y && player.m_nJump_Flag == JUMPDOWN)
		|| (player.x + 53 >= x && player.x + 53 <= x + 40 && player.y + 52>y - 45 && player.y + 52<y && player.m_nJump_Flag == JUMPDOWN))
	{
		return true;
	}
	return false;
}
void CMonster::InitItem(HINSTANCE hIns)
{
	m_hBmp_JumpItem = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_Monster));
}
void CMonster::JumpItemShow(HDC hdctemp)
{

	HDC hdc = CreateCompatibleDC(hdctemp);
	SelectObject(hdc, m_hBmp_JumpItem);
	BitBlt(hdctemp, x, y, 43, 55, hdc, 0, 0, SRCAND);
	DeleteDC(hdc);

}

