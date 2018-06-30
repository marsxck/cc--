#include "GameTable.h"



CGameTable::CGameTable()
{
	HB_TABLE = 0;
	x = rand()%(380-57);
	y = rand() % (550);
	m_ItemFlag = NO_ITEM;
	m_TableFlag = 0;
	//x = 100;
	//y = 100;
}


CGameTable::~CGameTable()
{
	DeleteObject(HB_TABLE);
	HB_TABLE = 0;
}
void CGameTable::GameTableInit(HINSTANCE hIns)
{
	HB_TABLE = LoadBitmap(hIns,MAKEINTRESOURCE(ID_HB_TABLE_ONE));
	
}
void CGameTable::GameTableShow(HDC hdc_src)
{
	HDC hdc_temp = CreateCompatibleDC(hdc_src);
	SelectObject(hdc_temp, HB_TABLE);
	BitBlt(hdc_src,x,y,57,15,hdc_temp,1,1,SRCAND);
	DeleteDC(hdc_temp);
}
bool CGameTable::IsPlayerJump(CPlayer &player)//判断角色底部是否接触踏板
{
	//只有角色下落时才可以触发跳跃
	if (player.m_nJump_Flag == JUMPUP)
	{
		return false;
	}
	
	//两点判断是否接触（x,y+53）(x+52,y+53)人52x53
	if (player.x<this->x + 57 && player.x>this->x&&player.y + 53 > this->y&&player.y + 53 < this->y + 15
		|| player.x + 52 < this->x + 57 && player.x + 52 > this->x&&player.y + 53 > this->y&&player.y + 53 < this->y + 15)
	{
		return true;
	}
	return false;
}



