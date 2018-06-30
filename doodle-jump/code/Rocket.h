#pragma once
#include "CItem.h"
class CRocket :
	public CItem
{
public:
	CRocket();
	~CRocket();
public:
	virtual bool IsTouchPlayer(CPlayer& player);
	virtual bool ItemJump(CPlayer& player);
	virtual void InitItem(HINSTANCE hIns);
	virtual void JumpItemShow(HDC hdctemp);
};

