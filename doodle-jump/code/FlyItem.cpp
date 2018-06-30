#include "FlyItem.h"



CFlyItem::CFlyItem()
{
	m_hBmp_JumpItem = 0;
	x = 0;
	y = 0;
}


CFlyItem::~CFlyItem()
{
	DeleteObject(m_hBmp_JumpItem);
	m_hBmp_JumpItem = 0;
}
bool CFlyItem::IsTouchPlayer(CPlayer& player)
{
	//ÎïÌå×ø±ê(x,y)(x,y+14)(x+21,y)(x+21,y+14)
	if (x >= player.x&&x <= player.x + 53 && y >= player.y&&y <= player.y + 52 ||
		x >= player.x&&x <= player.x + 53 && y + 14 >= player.y&&y + 14 <= player.y + 52 ||
		x + 21 >= player.x&&x + 21 <= player.x + 53 && y + 14 >= player.y&&y + 14 <= player.y + 52)
		return true;
	return false;
}
bool CFlyItem::ItemJump(CPlayer& player)
{
	return true;
}
void CFlyItem::InitItem(HINSTANCE hIns)
{
	m_hBmp_JumpItem = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_FLYITEM));
}
void CFlyItem::JumpItemShow(HDC hdctemp)
{
	HDC hdc = CreateCompatibleDC(hdctemp);
	SelectObject(hdc,m_hBmp_JumpItem);
	BitBlt(hdctemp,x,y,21,14,hdc,0,0,SRCAND);
	DeleteDC(hdc);
}