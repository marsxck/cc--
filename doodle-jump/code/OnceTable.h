#pragma once
#include "GameTable.h"
class COnceTable :
	public CGameTable
{
public:
	COnceTable();
	~COnceTable();
public:
	void GameTableInit(HINSTANCE hIns);

public:
	int m_oncetable;
};

