#include "MyThreadPool.h"


CMyThreadPool::CMyThreadPool(void)
{

	m_bFlagQuit = true;
	m_hSemphore = NULL;
	m_lCreateThreadNum= 0;
	m_lMaxThreadNum = 0;
	m_lRunThreadNum = 0;
}


CMyThreadPool::~CMyThreadPool(void)
{
}

//1.创建线程池
bool CMyThreadPool::CreateThreadPool(long lMinThreadNum, long lMaxThreadNum,long lMaxItaskNum)
{
	//校验参数
	if(lMinThreadNum <=0 || lMaxThreadNum < lMinThreadNum|| lMaxItaskNum <=0)
	{
		return false;
	}
	//初始化线程中的资源
	m_hSemphore = CreateSemaphore(NULL,0,lMaxItaskNum,NULL);
	if(!m_qItask.InitQueue(lMaxItaskNum/5))
	{
		return false;
	}

	//创建线程池
	for(long i = 0; i <lMinThreadNum;i++ )
	{
		HANDLE hThread = (HANDLE)_beginthreadex(0,0,&ThreadProc,this,0,0);
		if(hThread)
		{
			m_lstThread.push_back(hThread);
		}
	}

	m_lCreateThreadNum = lMinThreadNum;
	m_lMaxThreadNum = lMaxThreadNum;

	return true;
}

//2.销毁线程池
void  CMyThreadPool::DestroyThreadPool()
{
	m_bFlagQuit = false;
	auto ite = m_lstThread.begin();
	while(ite != m_lstThread.end())
	{

		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
		{
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite = NULL;
		ite++;
	}

	if(m_hSemphore)
	{
		CloseHandle(m_hSemphore);
		m_hSemphore = NULL;
	}

	//检查任务
	Itask *pItask = NULL;
	
	while(!m_qItask.empty())
	{
		if(m_qItask.pop(pItask))
		{
			delete pItask;
		     pItask = NULL;
		}
	
	}

	m_qItask.UnInitQueue();
}

//3.线程函数
unsigned _stdcall CMyThreadPool::ThreadProc( void * lpvoid )
{
	CMyThreadPool *pthis = (CMyThreadPool *)lpvoid;
	Itask *pItask = NULL;
	while(pthis->m_bFlagQuit)
	{
	      //等信号量
		if(WaitForSingleObject(pthis->m_hSemphore,INFINITE)!= WAIT_OBJECT_0)
		{
			continue;
		}
		//服务员切换状态   ---- 阻塞 ---就绪---运行
	 	//pthis->m_lRunThreadNum++;
		InterlockedIncrement(&pthis->m_lRunThreadNum);
		//从队列中去任务
		while(!pthis->m_qItask.empty())
		{
			
			if(!pthis->m_qItask.pop(pItask))
			{
				break;
			}
			pItask->RunItask();

			delete pItask;
			pItask = NULL;

		}

		//服务员切换状态   运行---- 阻塞
		//pthis->m_lRunThreadNum--;
		InterlockedDecrement(&pthis->m_lRunThreadNum);
	}

	return 0;
}

//4.投递任务
bool CMyThreadPool::PushItask(Itask *pItask)
{
	if(pItask == NULL) return false;

	//将任务加入到队列中
	//m_lock.Lock();
	//m_qItask.push(pItask);
	//m_lock.UnLock();
	
	
	 while(!m_qItask.push(pItask))
	 {
		 Sleep(10);
		
	 }

	//1. 有空闲服务员
	//释放信号量
	if(m_lRunThreadNum < m_lCreateThreadNum)
	{
	    ReleaseSemaphore(m_hSemphore,1,NULL);
	}
	else if(m_lRunThreadNum == m_lCreateThreadNum &&m_lCreateThreadNum < m_lMaxThreadNum )    //2.，没有空闲服务员，但是有桌
	{ 

	     //股服务员----干活
		HANDLE hThread = (HANDLE)_beginthreadex(0,0,&ThreadProc,this,0,0);
		if(hThread)
		{
			m_lstThread.push_back(hThread);
		}
		m_lCreateThreadNum++;
		ReleaseSemaphore(m_hSemphore,1,NULL);

	}
	else
	{
		//3 ，满了  ----客人等待
	}

	





	return true;
}
