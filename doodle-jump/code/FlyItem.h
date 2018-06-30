#pragma once
#include "CItem.h"
class CFlyItem :
	public CItem
{
public:
	CFlyItem();
	~CFlyItem();
public:
	virtual bool IsTouchPlayer(CPlayer& player);
	virtual bool ItemJump(CPlayer& player);
	virtual void InitItem(HINSTANCE hIns);
	virtual void JumpItemShow(HDC hdctemp);
};

