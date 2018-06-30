#pragma once
#include"CItem.h"
class CMonster2: public CItem
{
public:
	CMonster2();
	~CMonster2();
public:
	virtual bool IsTouchPlayer(CPlayer& player);
	virtual bool ItemJump(CPlayer& player);
	virtual void InitItem(HINSTANCE hIns);
	virtual void JumpItemShow(HDC hdctemp);
};

