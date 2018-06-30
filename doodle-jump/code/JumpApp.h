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
	list<CGameTable*> List_Table;//跳板链表
	list<CItem*> List_Jump;//道具链表
	list<CItem*> List_monster;
	list<CItem*> List_monster2;
	list<CItem*> List_blackhole;
	map<CGameTable*, CItem*> m_mapTableToItem;
	//map<CGameTable*, CItem*> Map_Monster_Table;
	//map<CGameTable*, CItem*> Map_Monster2_Table;
	//map<CGameTable*, CItem*> Map_BlackHole_Table;
public:
	static MCI_OPEN_PARMS m_mciOpen;  //打开参数
	static MCI_PLAY_PARMS m_mciPlay;  //播放参数
	HDC hdc_src;
	HDC hdc_temp;//缓冲去闪屏兼容dc
	HBITMAP hbitmap_temp;//缓冲去闪屏兼容位图
	int m_nScore;//分数
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
	static unsigned __stdcall ThreadProc(void *);//线程函数,控制角色左右位移
	//static unsigned __stdcall ThreadProcover(void *);//判断结束
	virtual void OnCreateGame();   // WM_CREATE

	virtual void OnGameDraw();     // WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID);      // WM_TIMER
	virtual void OnKeyDown(WPARAM nKey)
	{

	}
	void CreatJumpItem();//创建飞行道具
	
	void CreatTable();
	void AllItemShow();
	bool CreatTableRule(CGameTable* GameTable);
	bool IsTabJump();
	bool IsTouchFly();//是否碰到飞行道具
	void DeleteItem();
	void TableMove();
	/*void ItemMove();*/
	/*list<CGameTable*>::iterator ite;*/
	bool IsCreateTable();
	void FisTable();
	void FlyJump();
	void PlayMusic();
	void TableSort();
	void TableAction();//跳板的不同作用
	bool IsGameOver();//判断游戏是否结束
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



