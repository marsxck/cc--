#include "Player.h"



CPlayer::CPlayer()
{
	m_hBMP_palyer_Left = 0;
	m_hBMP_palyer_Rgiht = 0;
	m_hBMP_palyer_Fly = 0;
	y = 400;
	x = 190;
	m_nId = JUMPLEFTFLAG;
	m_nJump_Flag = JUMPUP;
	m_nFly = 0;

}
CPlayer::~CPlayer()
{
	DeleteObject(m_hBMP_palyer_Left);
	m_hBMP_palyer_Left = 0;
	DeleteObject(m_hBMP_palyer_Rgiht);
	m_hBMP_palyer_Rgiht = 0;
	DeleteObject(m_hBMP_palyer_Fly);
	m_hBMP_palyer_Fly = 0;
}
void CPlayer::JumpX(int fx)
{
	if (fx == JUMPLEFT)
	{
		x -= 1;
		m_nId = JUMPLEFTFLAG;
		if (x < 0)
		{
			x = 380;
		}
	}
	else if (fx==JUMPRIGHT)
	{
		x += 1;
		m_nId = JUMPRIGHTFLAG;
		if (x > 380)
		{
			x = 0;
		}
	}
}
void CPlayer::JumpY()
{
	if (m_nJump_Flag == JUMPUP)
	{
		y -= 5;
		length += 5;
		if (length > HIGHT)
		{
			m_nJump_Flag = JUMPDOWN;
			length = 0;
		}
		if(y<(LIMIT-100))
		{
			m_nJump_Flag = JUMPDOWN;
			length = 0;
		/*	Sleep(100);*/
		}
		
	}
	else if (m_nJump_Flag ==JUMPDOWN)
	{
		y += 4;
	}
	else if (m_nJump_Flag == JUMPFLY)
	{
		y -= 1;

		
	}
	else if (m_nJump_Flag == JUMPMONSTER)
	{
		
			y -= 1;


	}
}
void CPlayer::PlayerInit(HINSTANCE hIns)
{
	m_hBMP_palyer_Left = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_LEFT));
	m_hBMP_palyer_Rgiht = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_RIGHT));
	m_hBMP_palyer_Fly = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_FLYITEM));
	m_hBMP_palyer_Rocket = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_ROCKET));
}
void CPlayer::PlayerShow(HDC hdcmen)
{
	HDC hdctemp = CreateCompatibleDC(hdcmen);
	if (m_nId == JUMPLEFTFLAG)
	{
		SelectObject(hdctemp, m_hBMP_palyer_Left);
		BitBlt(hdcmen, x, y, 53, 52, hdctemp, 0, 0, SRCAND);
	}
		
	else if (m_nId == JUMPRIGHTFLAG)
	{
		SelectObject(hdctemp, m_hBMP_palyer_Rgiht);
		BitBlt(hdcmen, x+10, y, 53, 52, hdctemp, 0, 0, SRCAND);
	}
		
	
	if (m_nFly == JUMPFLY)
	{
		//HDC hdctemp = CreateCompatibleDC(hdcmen);
		SelectObject(hdctemp,m_hBMP_palyer_Fly);
		BitBlt(hdcmen,x+20,y,21,14,hdctemp,0,0,SRCAND);
	}
	if (m_nFly == JUMPROCKET&&m_nId == JUMPRIGHTFLAG)
	{
		//HDC hdctemp = CreateCompatibleDC(hdcmen);
		SelectObject(hdctemp, m_hBMP_palyer_Rgiht);
		BitBlt(hdcmen, x + 10, y, 53, 52, hdctemp, 0, 0, SRCAND);
		SelectObject(hdctemp, m_hBMP_palyer_Rocket);
		BitBlt(hdcmen, x-10, y+8, 25, 36, hdctemp, 0, 0, SRCAND);
	}
	if (m_nFly == JUMPROCKET&&m_nId == JUMPLEFTFLAG)
	{
		//HDC hdctemp = CreateCompatibleDC(hdcmen);
		SelectObject(hdctemp, m_hBMP_palyer_Left);
		BitBlt(hdcmen, x, y, 53, 52, hdctemp, 0, 0, SRCAND);
		SelectObject(hdctemp, m_hBMP_palyer_Rocket);
		BitBlt(hdcmen, x+49, y + 8, 25, 36, hdctemp, 0, 0, SRCAND);
	}

	DeleteDC(hdctemp);
}
