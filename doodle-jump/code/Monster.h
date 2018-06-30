#pragma once
#include "CItem.h"
class CMonster :
	public CItem
{
public:
	CMonster();
	~CMonster();
public:
	virtual bool IsTouchPlayer(CPlayer& player);
	virtual bool ItemJump(CPlayer& player);
	virtual void InitItem(HINSTANCE hIns);
	virtual void JumpItemShow(HDC hdctemp);
};

