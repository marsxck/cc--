#pragma once
#include"sys.h"
#include"Player.h"
#include"CItem.h"
class CGameTable
{
public:
	CGameTable();
	virtual~CGameTable();
	int x;
	int y;
	int m_ItemFlag;//板上是否有东西
	int m_TableFlag;//拿种板
	HBITMAP HB_TABLE;
public:
	virtual void GameTableShow(HDC hdc_src);
	virtual void GameTableInit(HINSTANCE hIns);
	virtual bool IsPlayerJump(CPlayer &player);
	virtual void TableAct(CItem*item) {};
	//bool IsCreatTable();
	
};

