#include "JumpApp.h"
#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库


IMPLEMENT(CJumpApp)
CJumpApp::CJumpApp()
{
	InitializeCriticalSection(&m_cs);
	hdc_src = 0;
	m_flag = false;
	m_nScore = 0;
	m_hThread = 0;
	m_ThreadFlag = true;
	back_flag = true;
	back_overflag = false;
	m_highscore = 0;
}
POINT Point;

int CJumpApp::platerlow = 0;
MCI_OPEN_PARMS CJumpApp::m_mciOpen = {0};  //打开参数
MCI_PLAY_PARMS CJumpApp::m_mciPlay = {0};  //播放参数
CJumpApp::~CJumpApp()
{
	ReleaseDC(m_hMainWnd,hdc_src);
	DeleteObject(hbitmap_temp);//删除兼容位图
	DeleteDC(hdc_temp);//删除缓冲dc
	list<CGameTable*>::iterator ite_table = List_Table.begin();
	while (ite_table != List_Table.end())
	{
		delete(*ite_table);
		ite_table++;
	}

	auto ite_monster = List_monster.begin();
	while (ite_monster != List_monster.begin())
	{
		delete(*ite_monster);
		ite_monster++;
	}

	auto ite_monster2 = List_monster2.begin();
	while (ite_monster2 != List_monster2.begin())
	{
		delete(*ite_monster2);
		ite_monster2++;
	}

	auto ite_blackhole = List_blackhole.begin();
	while (ite_blackhole != List_blackhole.begin())
	{
		delete(*ite_blackhole);
		ite_blackhole++;
	}

	m_mapTableToItem.clear();


	m_ThreadFlag = false;
	if (WAIT_TIMEOUT == WaitForSingleObject(m_hThread, 100))
	{
		TerminateThread(m_hThread, -1);
		CloseHandle(m_hThread);
		m_hThread = 0;
	}
	if (WAIT_TIMEOUT == WaitForSingleObject(m_hThread2, 100))
	{
		TerminateThread(m_hThread2, -1);
		CloseHandle(m_hThread2);
		m_hThread2 = 0;
	}
	DeleteCriticalSection(&m_cs);
}
void CJumpApp::OnCreateGame()
{

	/*PlaySound((LPCTSTR)IDR_WAVE1, m_hIns, SND_RESOURCE | SND_ASYNC);*/
	m_flag = false;
	hdc_src = GetDC(m_hMainWnd);//主dc
	hdc_temp = CreateCompatibleDC(hdc_src);//兼容缓冲dc
	hbitmap_temp = CreateCompatibleBitmap(hdc_src,380,550);//兼容最终贴图dc
	SelectObject(hdc_temp,hbitmap_temp);//兼容dc选入位图
	back.InitBack(m_hIns);
	UI.InitBack(m_hIns);
	UI2.InitBack(m_hIns);
	player.PlayerInit(m_hIns);
	m_score.InitScore(m_hIns);//初始化计数
	for (int i = 0; i < 18; i++)
	{
		this->CreatTable();
	}
	this->TableSort();
	SetTimer(m_hMainWnd, PLAYER_MOVE_TIMER,1,0);
	SetTimer(m_hMainWnd, TABLE_FIS_TIMER,2,0);
	SetTimer(m_hMainWnd, BACK_MOVE_TIMER, 10, 0);
	PlayMusic();
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc, this, 0, 0);
	SuspendThread(m_hThread2);
}

void CJumpApp::OnGameDraw()
{

	if (back_overflag == true)
	{
		
		if (Point.x>60 && Point.x<280 && Point.y>320 && Point.y<380)
		{

			SetTimer(m_hMainWnd, PLAYER_MOVE_TIMER, 1, 0);
			SetTimer(m_hMainWnd, TABLE_FIS_TIMER, 2, 0);
			SetTimer(m_hMainWnd, BACK_MOVE_TIMER, 10, 0);
			Point.x = 0;
			Point.y = 0;
			m_nScore = 0;
			player.y = 100;
			back_overflag = false;
		}
		if (Point.x>-120 && Point.x<200 && Point.y>400 && Point.y<480)
		{
			PostMessage(m_hMainWnd, WM_CLOSE, 0, 0);

		}
		this->ScoreCompare();
		UI2.BackShow(hdc_temp);
		this->ScoreSave();
		m_score.ShowScore(hdc_temp, m_nScore, 100, 150);
		m_score.ShowScore(hdc_temp, m_highscore, 100, 250);
		BitBlt(hdc_src, 0, 0, 380, 550, hdc_temp, 0, 0, SRCCOPY);
		return;
	}


	if (back_flag == true)
	{
		if (Point.x>50 && Point.x<280 && Point.y>370 && Point.y<450)
		{
			Point.x = 0;
			Point.y = 0;
			back_flag = false;
		}

		UI.BackShow(hdc_temp);
		BitBlt(hdc_src, 0, 0, 380, 550, hdc_temp, 0, 0, SRCCOPY);
		return;
	}

	if (this->m_nScore>10000)
	{
		back.Back2Show(hdc_temp);
	}
	else
	{
		back.BackShow(hdc_temp);
	}
	this->AllItemShow();
	player.PlayerShow(hdc_temp);
	m_score.ShowScore(hdc_temp, m_nScore);

	BitBlt(hdc_src, 0, 0, 380, 550, hdc_temp, 0, 0, SRCCOPY);
	//table.GameTableShow(hdc_src);
}

void CJumpApp::OnGameRun(WPARAM nTimerID)     // WM_TIMER
{
	if (back_flag == true)
	{
		this->OnGameDraw();
		return;
	}

	if (nTimerID == PLAYER_MOVE_TIMER)//人物左右移动
	{

		TableAction();
		this->PlayerHitMonster();
		this->PlayerHitMonster2();
		this->PlayerTouchBlackHole();
		if (this->IsGameOver())
		{
			ReStartGame();
		}
		this->CreatJumpItem();
		this->Monster2Create();
		this->MonsterCreate();
		this->BlackHoleCreate();
		if (this->IsCreateTable() == true && m_flag == false && platerlow<LIMIT + HIGHT /*player.y<150 && player.m_nJump_Flag == JUMPUP*/)
		{
		
			m_flag = true;
			this->TableMove();
		

		/*	back.FisBack(player);*/
			//if (platerlow == 300)
			//	return;
			//for (int i = 0; i < 8; i++)
			//{

			this->DeleteItem();

		}
		player.JumpY();
		if (IsGameOver())
		{
			ReStartGame();
		}
		if (this->IsTouchFly())
		{
			this->FlyJump();

		}
		if (this->IsTabJump())
			player.m_nJump_Flag = JUMPUP;
	}
	if (nTimerID== TABLE_FIS_TIMER)
	{
		//if (this->IsTabJump())
		//	player.m_nJump_Flag = JUMPUP;
		FisTable();
		FisTable();
		FisTable();
		TableSort();
	}
	if (nTimerID == BACK_MOVE_TIMER)
	{


		
	}
	
	this->OnGameDraw();
}
unsigned __stdcall CJumpApp::ThreadProc(void *volp)
{
	CJumpApp* pthis = (CJumpApp*)volp;
	while (pthis->m_ThreadFlag)
	{
		if (GetAsyncKeyState(VK_LEFT))
			pthis->player.JumpX(JUMPLEFT);
		if (GetAsyncKeyState(VK_RIGHT))
			pthis->player.JumpX(JUMPRIGHT);
		Sleep(5);

		//
		//if (pthis->IsGameOver())
		//{
		//	KillTimer(pthis->m_hMainWnd, PLAYER_MOVE_TIMER);
		//	KillTimer(pthis->m_hMainWnd, TABLE_FIS_TIMER);
		//	KillTimer(pthis->m_hMainWnd, BACK_MOVE_TIMER);
		//	MessageBox(pthis->m_hMainWnd, "over!", "text", MB_OK);
		//}

		//pthis->FisTable();
		//pthis->TableSort();
	}
	return 0;
}



bool CJumpApp::IsCreateTable()
{
	if (player.y<LIMIT && player.m_nJump_Flag == JUMPUP )
	{/*
		m_flag = true;*/
		
		return true;
	}
	return false;

}

void CJumpApp::TableMove()
{
	list<CGameTable*>::iterator ite_table = List_Table.begin();
	UINT i = 0;
	if (player.y<LIMIT && (player.m_nJump_Flag == JUMPUP||player.m_nJump_Flag ==JUMPFLY )/*&&platerlow<LIMIT + HIGHT*/&&platerlow&& (LIMIT - (platerlow - HIGHT))>0)
	{
	UINT flag = (LIMIT - (platerlow - HIGHT))/30 ;

		while (1)
		{
			
			while (ite_table != List_Table.end())
			{

				if (i >= List_Table.size()*flag)
				{
					if(flag>0)
					back.FisBack(player);
					
					return;
				}
				m_nScore += 1;//xiaobug

				

				if ((*ite_table)->m_ItemFlag == FLY_ITEM)
				{
					m_mapTableToItem[(*ite_table)]->y += 30;

				}
				if ((*ite_table)->m_ItemFlag == ROCKET_ITEM)
				{
					m_mapTableToItem[(*ite_table)]->y += 30;
				}
				if ((*ite_table)->m_ItemFlag == MONSTER_ITEM)
				{
					m_mapTableToItem[(*ite_table)]->y += 30;

					//if (m_mapTableToItem[(*ite_table)]->IsTouchPlayer(player) == true)
					//{
					//	ReStartGame();
					//}					

				}
				if (IsGameOver())
				{
					ReStartGame();
				}
				if ((*ite_table)->m_ItemFlag == MONSTER2_ITEM)
				{
					m_mapTableToItem[(*ite_table)]->y += 30;


				}

				if ((*ite_table)->m_ItemFlag == BLACK_HOLE_ITEM)
				{
					m_mapTableToItem[(*ite_table)]->y += 30;

					//if (m_mapTableToItem[(*ite_table)]->IsTouchPlayer(player) == true)
					//{
					//	ReStartGame();
					//}
				}

				
				(*ite_table)->y += 30;
	/*			if (IsGameOver())
				{
					ReStartGame();
				}*/
				i++;
				/*	(*ite_table)->y += 50;*/
				/*player.y += LIMIT - (platerlow - HIGHT);*/
				
				
				
				this->OnGameDraw();

				ite_table++;
			}
			ite_table = List_Table.begin();
		}
	}


}
void CJumpApp::DeleteItem()
{
	list<CGameTable*>::iterator ite_table = List_Table.begin();
	while (ite_table != List_Table.end())
	{
		if ((*ite_table)->y>=650)
		{
			auto itemap = m_mapTableToItem.begin();
			while (itemap != m_mapTableToItem.end())
			{
				if (itemap->first == *ite_table)
				{
					m_mapTableToItem.erase(itemap);
					break;
				}
				itemap++;
			}
			auto itetom = m_mapTableToItem.begin();
			while (itetom != m_mapTableToItem.end())
			{
				if (itetom->first == *ite_table)
				{
					m_mapTableToItem.erase(itetom);
					break;
				}
				itetom++;
			}
			delete(*ite_table);
			ite_table = List_Table.erase(ite_table);
		}
		else
		ite_table++;
	}

	list<CItem*>::iterator ite_Jump = List_Jump.begin();
	while (ite_Jump != List_Jump.end())
	{
		if ((*ite_Jump)->y>=650)
		{
			auto itemap = m_mapTableToItem.begin();
			while (itemap != m_mapTableToItem.end())
			{
				if (itemap->second==*ite_Jump)
				{
					m_mapTableToItem.erase(itemap);
					break;
				}
				itemap++;
			}
			delete(*ite_Jump);
			ite_Jump = List_Jump.erase(ite_Jump);
			
			
		}
		else
		{
			ite_Jump++;
		}
	}

	list<CItem*>::iterator ite_monster = List_monster.begin();
	while (ite_monster != List_monster.end())
	{
		if ((*ite_monster)->y>=650)
		{
			auto itetom = m_mapTableToItem.begin();
			while (itetom != m_mapTableToItem.end())
			{
				if (itetom->second == *ite_monster)
				{
					m_mapTableToItem.erase(itetom);
					break;
				}
				itetom++;
			}
			delete(*ite_monster);
			ite_monster = List_monster.erase(ite_monster);
		}
		else
		{
			ite_monster++;
		}
	}

	list<CItem*>::iterator ite_monster2 = List_monster2.begin();
	while (ite_monster2 != List_monster2.end())
	{
		if ((*ite_monster2)->y>=650)
		{
			delete(*ite_monster2);
			ite_monster2 = List_monster2.erase(ite_monster2);
		}
		else
		{
			ite_monster2++;
		}
	}
	
	list<CItem*>::iterator ite_blackhole = List_blackhole.begin();
	while (ite_blackhole != List_blackhole.end())
	{
		if ((*ite_blackhole)->y>=650)
		{
			delete(*ite_blackhole);
			ite_blackhole = List_blackhole.erase(ite_blackhole);
		}
		else
		{
			ite_blackhole++;
		}
	}
}
void CJumpApp::TableAction()
{
	list<CGameTable*>::iterator ite = List_Table.begin();
	while (ite != List_Table.end())
	{
		if ((*ite)->m_ItemFlag == FLY_ITEM|| (*ite)->m_ItemFlag == ROCKET_ITEM)
		{
			(*ite)->TableAct(m_mapTableToItem[*ite]);
		}
		if ((*ite)->m_ItemFlag == MONSTER_ITEM)
		{
			(*ite)->TableAct(m_mapTableToItem[*ite]);
		}
		if ((*ite)->m_ItemFlag == MONSTER2_ITEM)
		{
			(*ite)->TableAct(m_mapTableToItem[*ite]);
		}
		if ((*ite)->m_ItemFlag == BLACK_HOLE_ITEM)
		{
			(*ite)->TableAct(m_mapTableToItem[*ite]);
		}
		(*ite)->TableAct(NULL);
		++ite;
	}

}
void CJumpApp::CreatTable()
{

		CGameTable* GameTable = new CGameTable;
		if (this->CreatTableRule(GameTable) == true)
		{
			GameTable->GameTableInit(m_hIns);
			List_Table.push_back(GameTable);
		}
		else
		{
			delete GameTable;
		}

	
}
void CJumpApp::AllItemShow()//显示所有跳板
{
	list<CGameTable*>::iterator ite = List_Table.begin();
	while (ite != List_Table.end())
	{
		(*ite)->GameTableShow(hdc_temp);
		++ite;
	}
	list<CItem*>::iterator ite_Jump = List_Jump.begin();
	while (ite_Jump != List_Jump.end())
	{
		(*ite_Jump)->JumpItemShow(hdc_temp);
		++ite_Jump;
	}

	auto ite_monster = List_monster.begin();
	while (ite_monster != List_monster.end())
	{
		(*ite_monster)->JumpItemShow(hdc_temp);
		ite_monster++;
	}

	auto ite_monster2 = List_monster2.begin();
	while (ite_monster2 != List_monster2.end())
	{
		(*ite_monster2)->JumpItemShow(hdc_temp);
		ite_monster2++;
	}

	auto ite_blackhole = List_blackhole.begin();
	while (ite_blackhole != List_blackhole.end())
	{
		(*ite_blackhole)->JumpItemShow(hdc_temp);
		ite_blackhole++;
	}
}

bool CJumpApp::CreatTableRule(CGameTable* GameTable)//判断跳板是否重叠
{
	//三点法，1. (x+28,y) 2. (x,y+15) 3. (x+57,y+15) 
	//四点    x,y   x+62,y  x,y+17 x+62,y+17
	list<CGameTable*>::iterator ite = List_Table.begin();
	while (ite != List_Table.end())
	{
		if ((GameTable->x)>=((*ite)->x)&&(GameTable->x)<=((*ite)->x+57)
			&& (GameTable->y)>=((*ite)->y)&&(GameTable->y)<=((*ite)->y + 15)
			|| (GameTable->x+57)>=((*ite)->x)&&(GameTable->x+57)<=((*ite)->x + 57)
			&& (GameTable->y)>=((*ite)->y)&&(GameTable->y)<=((*ite)->y + 15)
			|| (GameTable->x)>=((*ite)->x)&&(GameTable->x)<=((*ite)->x + 57)
			&& (GameTable->y+15)>=((*ite)->y)&&(GameTable->y+15)<=((*ite)->y + 15)
			|| (GameTable->x + 57) >= ((*ite)->x) && (GameTable->x + 57) <= ((*ite)->x + 57)
			&& (GameTable->y + 15) >= ((*ite)->y) && (GameTable->y + 15) <= ((*ite)->y + 15))
		{
			return false;
		}
		++ite;
	}
	return true;
}
bool  CJumpApp::IsTabJump()
{
	list<CGameTable*>::iterator itetable = List_Table.begin();
	while (itetable != List_Table.end())
	{
		if ((*itetable)->IsPlayerJump(player))
		{
			platerlow = (*itetable)->y;
			m_flag = false;
			/*PlaySound("res\\jup.wav", NULL,SND_FILENAME | SND_ASYNC| SND_NODEFAULT);*/
			PlaySound((LPCTSTR)IDR_WAVE1, m_hIns, SND_RESOURCE | SND_ASYNC);
			if ((*itetable)->m_TableFlag == ONCE_TABLE)
			{
				(*itetable)->y = 580;
				if ((*itetable)->m_ItemFlag == FLY_ITEM)
				{
					m_mapTableToItem[*itetable]->y = 600;
				}
				if ((*itetable)->m_ItemFlag== MONSTER2_ITEM)
				{
					m_mapTableToItem[*itetable]->y = 600;
				}
				if ((*itetable)->m_ItemFlag == MONSTER_ITEM)
				{
					m_mapTableToItem[*itetable]->y = 600;
				}
				if ((*itetable)->m_ItemFlag == BLACK_HOLE_ITEM)
				{
					m_mapTableToItem[*itetable]->y = 600;
				}
				if ((*itetable)->m_ItemFlag == ROCKET_ITEM)
				{
					m_mapTableToItem[*itetable]->y = 600;
				}
			}
			return true;
		}

		++itetable;
	}
	return false;
}
bool CJumpApp::IsTouchFly()
{
	list<CGameTable*>::iterator ite = List_Table.begin();
	while (ite != List_Table.end())
	{
		if ((*ite)->m_ItemFlag == FLY_ITEM)
		{
			//有问题
			if (m_mapTableToItem[*ite]->m_hBmp_JumpItem == NULL) return false;
			if (m_mapTableToItem[*ite]->IsTouchPlayer(player))
			{
				m_mapTableToItem[*ite]->y = 650;
				(*ite)->m_ItemFlag = NO_ITEM;
				player.m_nFly = JUMPFLY;
				player.m_nJump_Flag = JUMPFLY;
				PlaySound((LPCTSTR)IDR_WAVE2, m_hIns, SND_RESOURCE | SND_ASYNC);
				return true;
			}

		}
		if ((*ite)->m_ItemFlag == ROCKET_ITEM)
		{
			//有问题
			if (m_mapTableToItem[*ite]->m_hBmp_JumpItem == NULL) return false;
			if (m_mapTableToItem[*ite]->IsTouchPlayer(player))
			{
				m_mapTableToItem[*ite]->y = 650;
				(*ite)->m_ItemFlag = NO_ITEM;
				player.m_nFly = JUMPROCKET;
				player.m_nJump_Flag = JUMPFLY;
				PlaySound((LPCTSTR)IDR_WAVE3, m_hIns, SND_RESOURCE | SND_ASYNC);
				/*PlaySound((LPCTSTR)IDR_WAVE2, m_hIns, SND_RESOURCE | SND_ASYNC);*/
				return true;
			}

		}

		++ite;
	}
	return false;
}
void CJumpApp::FisTable()//在屏幕外刷新跳板
{
	int index = rand() % 4;
	CGameTable* GameTable = NULL;
	if (index == 1)
	{
		GameTable = new CMoveTable;
	}
	else if (index==2)
	{
		GameTable = new COnceTable;
		GameTable->m_TableFlag = ONCE_TABLE;
	}
	else
	{
		GameTable = new CGameTable;
		
	}
	
	GameTable->y = -rand() % 850 - 20;
	if (this->CreatTableRule(GameTable) == true)
	{
		GameTable->GameTableInit(m_hIns);
		List_Table.push_back(GameTable);
	}
	else
	{
		delete GameTable;
		GameTable = NULL;
	}

}
void CJumpApp::ReStartGame()//重新开始游戏
{
	
	ResumeThread(m_hThread2);
	KillTimer(m_hMainWnd, PLAYER_MOVE_TIMER);
	KillTimer(m_hMainWnd, TABLE_FIS_TIMER);
	KillTimer(m_hMainWnd, BACK_MOVE_TIMER);
	SetTimer(m_hMainWnd, GAME_OVER_TIMER, 10, 0);
	//this->ScoreSave();
	back_overflag = true;
	if (m_highscore==0)
	{
		m_highscore = m_nScore;
	}
	this->OnGameDraw();
	/*MessageBox(m_hMainWnd, "over!", "text", MB_OK);
	player.x = 250;
	player.y = 100;
	SetTimer(m_hMainWnd, PLAYER_MOVE_TIMER, 1, 0);
	SetTimer(m_hMainWnd, TABLE_FIS_TIMER, 2, 0);
	SetTimer(m_hMainWnd, BACK_MOVE_TIMER, 10, 0);*/
	//m_nScore = 0;
}
void CJumpApp::PlayMusic()
{
	m_mciOpen.lpstrDeviceType = "mpegvideo"; //要操作的文件类型
	m_mciOpen.lpstrElementName = "res\\music.mp3"; //要操作的文件路径
	MCIERROR mcierror = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&m_mciOpen); //打开文件命令
	if (mcierror) {
		char buf[128] = { 0 };
		mciGetErrorString(mcierror, buf, 128);
		MessageBox(m_hMainWnd, buf, NULL, 0);
	}
	else {
		m_mciPlay.dwCallback = (DWORD)m_hMainWnd;
		m_mciPlay.dwFrom = (DWORD)(0); //播放起始位置ms为单位
		mciSendCommand(m_mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)(LPVOID)&m_mciPlay);
	}
}
void CJumpApp::TableSort()
{
	list<CGameTable*>::iterator itetable = List_Table.begin();

	CGameTable* temp = nullptr;
	int nLength = List_Table.size();
	for (int i = 0; i<nLength - 1; i++)
	{
		for (int j = 0; j<nLength - 1 - i; j++)
		{
			if ((*itetable)->y < (*(++itetable))->y)
			{
				itetable--;
				temp = *(++itetable);
				itetable--;
				*(++itetable) = (*itetable);

				itetable--;
				(*itetable) = temp;
				++itetable;

			}
		}
		itetable = List_Table.begin();
	}

	itetable = List_Table.begin();
	while (itetable != List_Table.end())
	{


		while (1)
		{
			if ((*itetable)->y > 0)
			{
				itetable++;
				if (itetable == List_Table.end())
					return;
				if (++itetable == List_Table.end())
				{
					itetable--;
					return;
				}
				else
				{
					itetable--;
				}
				
					
			}
			else
			{
			/*	itetable--;*/
				break;
			}
		}
		int nLength = (*itetable)->y - (*(++itetable))->y;
		if (nLength<25 /*||nLength>100*/)
		{

			itetable--;
			
			if ((*itetable)->m_ItemFlag == FLY_ITEM|| (*itetable)->m_ItemFlag == ROCKET_ITEM)
			{
				list<CItem*>::iterator ite_Jump = List_Jump.begin();
				while (ite_Jump != List_Jump.end())
				{
					if (m_mapTableToItem[*itetable] == *ite_Jump)
					{
						auto itetom = m_mapTableToItem.begin();
						while (itetom != m_mapTableToItem.end())
						{
							if (itetom->second == *ite_Jump)
							{
								m_mapTableToItem.erase(itetom);//删除映射
								break;
							}
							itetom++;
						}
						delete  *ite_Jump;
						List_Jump.erase(ite_Jump);//删除链表
						break;
					}
					ite_Jump++;
						
				}
				
			}
			if ((*itetable)->m_ItemFlag == MONSTER_ITEM)
			{
				list<CItem*>::iterator ite_mon = List_monster.begin();
				while (ite_mon != List_monster.end())
				{
					if (m_mapTableToItem[*itetable] == *ite_mon)
					{

						auto itetom = m_mapTableToItem.begin();
						while (itetom != m_mapTableToItem.end())
						{
							if (itetom->second == *ite_mon)
							{
								m_mapTableToItem.erase(itetom);
								break;
							}
							itetom++;
						}
						delete  *ite_mon;
						List_monster.erase(ite_mon);
					}
					ite_mon++;

				}

			}
			if ((*itetable)->m_ItemFlag == MONSTER2_ITEM)
			{
				list<CItem*>::iterator ite_mon = List_monster2.begin();
				while (ite_mon != List_monster2.end())
				{
					if (m_mapTableToItem[*itetable] == *ite_mon)
					{

						auto itetom = m_mapTableToItem.begin();
						while (itetom != m_mapTableToItem.end())
						{
							if (itetom->second == *ite_mon)
							{
								m_mapTableToItem.erase(itetom);
								break;
							}
							itetom++;
						}
						delete  *ite_mon;
						List_monster2.erase(ite_mon);
					}
					ite_mon++;

				}

			}//////////////////////
			if ((*itetable)->m_ItemFlag == BLACK_HOLE_ITEM)
			{
				list<CItem*>::iterator ite_mon = List_blackhole.begin();
				while (ite_mon != List_blackhole.end())
				{
					if (m_mapTableToItem[*itetable] == *ite_mon)
					{

						auto itetom = m_mapTableToItem.begin();
						while (itetom != m_mapTableToItem.end())
						{
							if (itetom->second == *ite_mon)
							{
								m_mapTableToItem.erase(itetom);
								break;
							}
							itetom++;
						}
						delete  *ite_mon;
						List_blackhole.erase(ite_mon);
					}
					ite_mon++;

				}

			}//////////////////////
			delete (*itetable);
			itetable = List_Table.erase(itetable);

		}
		if (nLength>70)
		{
			itetable--;
			CGameTable* GameTable = new CGameTable;
			GameTable->y = (*(++itetable))->y + rand() % nLength;
			itetable--;
			GameTable->GameTableInit(m_hIns);
			List_Table.insert((++itetable), GameTable);
			/*itetable--;*/
		}

		if (++itetable == List_Table.end())
		{
			break;
		}
		itetable--;

	}


}
bool CJumpApp::IsGameOver()
{
	if (player.y > 500)
	{
		return true;
	}
	list<CGameTable*>::iterator ite_table = List_Table.begin();
	while (ite_table != List_Table.end())
	{
		if ((*ite_table)->m_ItemFlag != NO_ITEM && (*ite_table)->m_ItemFlag != FLY_ITEM&& (*ite_table)->m_ItemFlag != ROCKET_ITEM)
		{
			if (m_mapTableToItem[*ite_table] == NULL)
			{
	
				return false;
			}
			if (m_mapTableToItem[*ite_table]->IsTouchPlayer(player))
			{
				m_mapTableToItem[*ite_table]->x = -367;
				return true;
			}
		}
		ite_table++;
	}
	return false;
}
void CJumpApp::CreatJumpItem()
{
	if (List_Jump.size() > 4) return;
	CItem* jumpitem = NULL;
	if (rand() % 2 != 1)
	{
		jumpitem = new CFlyItem;
		jumpitem->style = FLY_ITEM;
	}
	else
	{
		jumpitem = new CRocket;
		jumpitem->style = ROCKET_ITEM;
	}
	jumpitem->InitItem(m_hIns);
	int index=rand() % List_Table.size();
	auto ite_table = List_Table.begin();
	for (int i = 0; i < index; i++)
		ite_table++;
	if ((*ite_table)->m_ItemFlag != NO_ITEM && (*ite_table)->m_ItemFlag != BLACK_HOLE_ITEM
		&& (*ite_table)->m_ItemFlag != NO_MONSTER2_ITEM && (*ite_table)->m_ItemFlag != NO_MONSTER_ITEM)
	{
		delete jumpitem;
		return;
	}
	if ((*ite_table)->y>0)
	{
		delete jumpitem;
		return;
	}
	if (jumpitem->style == FLY_ITEM)
	{
		jumpitem->x = (*ite_table)->x + 15;
		jumpitem->y = (*ite_table)->y - 14;
		(*ite_table)->m_ItemFlag = FLY_ITEM;//板上有东西
	}
	if (jumpitem->style==ROCKET_ITEM)
	{
		jumpitem->x = (*ite_table)->x + 13;
		jumpitem->y = (*ite_table)->y - 34;
		(*ite_table)->m_ItemFlag = ROCKET_ITEM;//板上有东西
	}
	m_mapTableToItem[*ite_table] = jumpitem;
	List_Jump.push_back(jumpitem);
}
void CJumpApp::FlyJump()
{
	while (player.y>220)
	{
		player.y -= 3;
		this->OnGameDraw();
	}
	platerlow = 220;
	if (player.m_nFly == JUMPFLY)
	{
		for (int i = 0; i < 5; i++)
		{
			player.JumpY();
			if (back_overflag==true)
			{
				player.m_nJump_Flag = JUMPDOWN;
				player.m_nFly = 0;
				return;
			}
			this->OnGameDraw();
			this->TableMove();
			this->FisTable();
			this->FisTable();
			this->FisTable();
			this->FisTable();
			this->TableSort();

		}
	}
	if (player.m_nFly == JUMPROCKET)
	{
		for (int i = 0; i < 10; i++)
		{
			player.JumpY();
			if (back_overflag == true)
			{
				player.m_nJump_Flag = JUMPDOWN;
				player.m_nFly = 0;
				return;
			}
			this->OnGameDraw();
			this->TableMove();
			this->FisTable();
			this->FisTable();
			this->FisTable();
			this->FisTable();
			this->TableSort();

		}
	}

	player.m_nJump_Flag = JUMPDOWN;
	player.m_nFly = 0;
	this->DeleteItem();
}
void CJumpApp::MonsterCreate()
{
	if (rand() % 10 != 3) return;
	CItem* monster = new CMonster;
	monster->InitItem(m_hIns);
	auto ite_table = List_Table.begin();
	int i = rand() % (List_Table.size());
	for (int j = 0;j<i;j++)
	{
		ite_table++;
	}

	if ((*ite_table)->m_ItemFlag != NO_ITEM && (*ite_table)->m_ItemFlag != BLACK_HOLE_ITEM
		&& (*ite_table)->m_ItemFlag != NO_MONSTER2_ITEM && (*ite_table)->m_ItemFlag != NO_MONSTER_ITEM)
	{
		delete monster;
		return;
	}
	if ((*ite_table)->y>0)
	{
		delete monster;
		return;
	}
	monster->x = (*ite_table)->x + 10;
	monster->y = (*ite_table)->y - 45;
	m_mapTableToItem[(*ite_table)] = monster;
	(*ite_table)->m_ItemFlag = MONSTER_ITEM;
	List_monster.push_back(monster);
}
void CJumpApp::PlayerHitMonster()
{
	auto ite_monster = List_monster.begin();
	auto ite_table = List_Table.begin();
	while (ite_monster != List_monster.end())
	{
		if ((*ite_monster)->ItemJump(player) == true)
		{


			while (ite_table != List_Table.end())
			{
				if (m_mapTableToItem[(*ite_table)] == (*ite_monster))
				{
					m_mapTableToItem.erase((*ite_table));
					(*ite_table)->m_ItemFlag = NO_MONSTER_ITEM;
				}
				ite_table++;
			}
			player.m_nJump_Flag = JUMPUP;
			platerlow = (*ite_monster)->y-50;
			PlaySound((LPCTSTR)IDR_WAVE1, m_hIns, SND_RESOURCE | SND_ASYNC);
			(*ite_monster)->y = 650;

		}
		else
		{
			ite_monster++;
		}
	}
}
void CJumpApp::PlayerHitMonster2()
{
	auto ite_monster = List_monster2.begin();
	auto ite_table = List_Table.begin();
	while (ite_monster != List_monster2.end())
	{
		if ((*ite_monster)->ItemJump(player) == true)
		{


			while (ite_table != List_Table.end())
			{
				if (m_mapTableToItem[(*ite_table)] == (*ite_monster))
				{
					m_mapTableToItem.erase((*ite_table));
					(*ite_table)->m_ItemFlag = NO_MONSTER2_ITEM;
				}
				ite_table++;
			}
			player.m_nJump_Flag = JUMPUP;
			platerlow = (*ite_monster)->y-50;
			PlaySound((LPCTSTR)IDR_WAVE1, m_hIns, SND_RESOURCE | SND_ASYNC);
			(*ite_monster)->y = 650;
		}
		else
		{
			ite_monster++;
		}
	}
}
void CJumpApp::Monster2Create()
{
	if (rand() % 10 != 3) return;
	CItem* monster = new CMonster2;
	monster->InitItem(m_hIns);
	auto ite_table = List_Table.begin();
	int i = rand() % (List_Table.size());
	for (int j = 0;j<i;j++)
	{
		ite_table++;
	}

	if ((*ite_table)->m_ItemFlag != NO_ITEM && (*ite_table)->m_ItemFlag != BLACK_HOLE_ITEM
		&& (*ite_table)->m_ItemFlag != NO_MONSTER2_ITEM && (*ite_table)->m_ItemFlag != NO_MONSTER_ITEM)
	{
		delete monster;
		return;
	}
	if ((*ite_table)->y>0)
	{
		delete monster;
		return;
	}
	monster->x = (*ite_table)->x-10;
	monster->y = (*ite_table)->y - 50;
	m_mapTableToItem[(*ite_table)] = monster;
	(*ite_table)->m_ItemFlag = MONSTER2_ITEM;
	List_monster2.push_back(monster);
}
void CJumpApp::BlackHoleCreate()
{
	/*if (List_blackhole.size() > 2) return;*/
	if (rand() % 14 != 3) return;
	CItem* blackhole = new CBlackHole;
	blackhole->InitItem(m_hIns);
	auto ite_table = List_Table.begin();
	int i = rand() % (List_Table.size());
	for (int j = 0;j<i;j++)
	{
		ite_table++;
	}

	if ((*ite_table)->m_ItemFlag != NO_ITEM && (*ite_table)->m_ItemFlag != BLACK_HOLE_ITEM 
		&& (*ite_table)->m_ItemFlag != NO_MONSTER2_ITEM && (*ite_table)->m_ItemFlag != NO_MONSTER_ITEM)
	{
		delete blackhole;
		return;
	}
	if ((*ite_table)->y>0)
	{
		delete blackhole;
		return;
	}
	blackhole->x = (*ite_table)->x;
	blackhole->y = (*ite_table)->y - 70;
	m_mapTableToItem[(*ite_table)] = blackhole;
	(*ite_table)->m_ItemFlag = BLACK_HOLE_ITEM;
	List_blackhole.push_back(blackhole);
	
}
void CJumpApp::PlayerTouchBlackHole()
{
	auto ite_blackhole = List_blackhole.begin();
	auto ite_table = List_Table.begin();
	while (ite_blackhole != List_blackhole.end())
	{
		if ((*ite_blackhole)->IsTouchPlayer(player) == true)
		{
			(*ite_blackhole)->x = -330;
			ReStartGame();
		}

			ite_blackhole++;
		
	}
}
void CJumpApp::ScoreCompare()
{
	FILE* file = NULL;
	char buf[100] = { 0 };
	/*itoa(m_nScore, buf, 10);*/
	fopen_s(&file, "score.txt", "r");
	fread_s(buf, 100, 10, 1, file);
	m_highscore=atoi(buf);
	if (m_highscore<m_nScore)
	{
		m_highscore = m_nScore;
	}
	fclose(file);
}
void CJumpApp::ScoreSave()
{
	FILE* file = NULL;
	char buf[100] = { 0 };
	_itoa_s(m_highscore, buf, 100,10);
	fopen_s(&file, "score.txt", "w+");
	fwrite(buf, 10, 1, file);
	fclose(file);
}




