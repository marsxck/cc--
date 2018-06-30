#pragma once
#include"sys.h"
class CPlayer
{
public:
	HBITMAP m_hBMP_palyer_Rgiht;
	HBITMAP m_hBMP_palyer_Left;
	HBITMAP m_hBMP_palyer_Fly;
	HBITMAP m_hBMP_palyer_Rocket;
	int x;
	int y;
	int length;
	int m_nId;
	int m_nJump_Flag;
	int m_nFly;//÷стят—
	/*int playerlow;*/
public:
	void JumpX(int fx);
	void JumpY();
	void PlayerInit(HINSTANCE hIns);
	void PlayerShow(HDC hdcmen);
	CPlayer();
	~CPlayer();
};

