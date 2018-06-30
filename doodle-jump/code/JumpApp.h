#pragma once
#include"FlyItem.h"
#include "CGameCtrl.h"
#include"Back.h"
#include"sys.h"
#include"MoveTable.h"
#include"Player.h"
#include<process.h>
#include"Score.h"
#include<map>
#include"Monster.h"
#include"Monster2.h"
#include"BlackHole.h"
#include"OnceTable.h"
#include"Rocket.h"
#include"UI.h"
#include"UI2.h"
#ifndef _JUMP_H_
#define _JUMP_H_
extern POINT Point;

class CJumpApp :
	public CGameCtrl
{

public:
	CJumpApp();
	~CJumpApp();
	list<CGameTable*> List_Table;//��������
	list<CItem*> List_Jump;//��������
	list<CItem*> List_monster;
	list<CItem*> List_monster2;
	list<CItem*> List_blackhole;
	map<CGameTable*, CItem*> m_mapTableToItem;
	//map<CGameTable*, CItem*> Map_Monster_Table;
	//map<CGameTable*, CItem*> Map_Monster2_Table;
	//map<CGameTable*, CItem*> Map_BlackHole_Table;
public:
	static MCI_OPEN_PARMS m_mciOpen;  //�򿪲���
	static MCI_PLAY_PARMS m_mciPlay;  //���Ų���
	HDC hdc_src;
	HDC hdc_temp;//����ȥ��������dc
	HBITMAP hbitmap_temp;//����ȥ��������λͼ
	int m_nScore;//����
	DECLARE()
	CBack back;
	CUI UI;
	CUI2 UI2;
	CScore m_score;
	CPlayer player;
	bool m_flag;
	static int platerlow;	
	HANDLE m_hThread;
	HANDLE m_hThread2;
	CRITICAL_SECTION m_cs;
	/*HANDLE m_hThreadover;*/
	bool m_ThreadFlag;
	bool back_flag;
	bool back_overflag;
	int m_highscore;
public:
	static unsigned __stdcall ThreadProc(void *);//�̺߳���,���ƽ�ɫ����λ��
	//static unsigned __stdcall ThreadProcover(void *);//�жϽ���
	virtual void OnCreateGame();   // WM_CREATE

	virtual void OnGameDraw();     // WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID);      // WM_TIMER
	virtual void OnKeyDown(WPARAM nKey)
	{

	}
	void CreatJumpItem();//�������е���
	
	void CreatTable();
	void AllItemShow();
	bool CreatTableRule(CGameTable* GameTable);
	bool IsTabJump();
	bool IsTouchFly();//�Ƿ��������е���
	void DeleteItem();
	void TableMove();
	/*void ItemMove();*/
	/*list<CGameTable*>::iterator ite;*/
	bool IsCreateTable();
	void FisTable();
	void FlyJump();
	void PlayMusic();
	void TableSort();
	void TableAction();//����Ĳ�ͬ����
	bool IsGameOver();//�ж���Ϸ�Ƿ����
	void PlayerHitMonster();
	void MonsterCreate();
	void PlayerHitMonster2();
	void Monster2Create();
	void BlackHoleCreate();
	void PlayerTouchBlackHole();
	void ReStartGame();
	void ScoreCompare();
	void ScoreSave();
	
};


#endif // _JUMP_H_



