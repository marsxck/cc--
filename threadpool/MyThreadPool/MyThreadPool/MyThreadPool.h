#pragma once
#include <process.h>
#include <Windows.h>
#include <list>
#include <queue>
#include "MyQueue.h"
using namespace std;
#define MAX_LEN   1000

class Itask
{
public:
	Itask(){};
	virtual~Itask(){};
public:
	virtual void RunItask() = 0;
private:

};

class CMyThreadPool
{
public:
	CMyThreadPool(void);
	~CMyThreadPool(void);
public:
	//1.创建线程池
	   bool CreateThreadPool(long lMinThreadNum, long lMaxThreadNum,long lMaxItaskNum = MAX_LEN);

	//2.销毁线程池
	   void  DestroyThreadPool();

	//3.线程函数
	  static  unsigned _stdcall ThreadProc( void * );

	//4.投递任务
	  bool PushItask(Itask *);
private:
	//线程句柄
	list<HANDLE> m_lstThread;
	HANDLE       m_hSemphore;
	bool    m_bFlagQuit;
	//queue<Itask*> m_qItask;
	long    m_lCreateThreadNum;
	long    m_lMaxThreadNum;
	/*volatile*/ long    m_lRunThreadNum;
	//CMyLock m_lock;
	MyQueue<Itask*> m_qItask;
};

