#pragma once
#include"sys.h"
#include"Player.h"
class CItem
{
public:
	CItem() { style = 0; };
	virtual~CItem() {};
public:
	virtual bool IsTouchPlayer(CPlayer& player)=0;
	virtual bool ItemJump(CPlayer& player) = 0;
	virtual void InitItem(HINSTANCE hIns)=0;
	virtual void JumpItemShow(HDC hdctemp) = 0;

public:
	int x;
	int y;
	HBITMAP m_hBmp_JumpItem;
	int style;

};


