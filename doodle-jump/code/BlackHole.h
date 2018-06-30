#pragma once
#include "CItem.h"
class CBlackHole :
	public CItem
{
public:
	CBlackHole();
	~CBlackHole();
	virtual bool IsTouchPlayer(CPlayer& player);
	virtual bool ItemJump(CPlayer& player);
	virtual void InitItem(HINSTANCE hIns);
	virtual void JumpItemShow(HDC hdctemp);
};

