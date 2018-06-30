#pragma once
#include "GameTable.h"

class CMoveTable :
	public CGameTable
{
public:
	CMoveTable();
	~CMoveTable();
public:
	void GameTableInit(HINSTANCE hIns);
	void TableAct(CItem*item);
private:
	int m_nMoveFlag;
};

