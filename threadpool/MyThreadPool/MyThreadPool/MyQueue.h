
#ifndef  _MYQUEUE_H
#define _MYQUEUE_H
#include "CMyLock.h"

template <typename T>
class MyQueue
{
public:
	MyQueue()
	{
		m_queue = nullptr;

		m_lWritePos = 0;
		m_lReadPos = 0;
		m_nLen = 0;
	}
	~MyQueue()
	{}

	//1.创建环形缓冲区
	bool  InitQueue(int nLen)
	{  
		if(nLen <=0)
		{
			return false;
		}

		m_queue = new T[nLen];
		m_nLen = nLen;
		//初始化队列
		for(int i = 0;i <nLen;i++ )
		{
			m_queue[i] = nullptr;
		}

		return true;
	}

	//2.销毁缓冲区
	void UnInitQueue()
	{
	
	    if(m_queue)
		{
			delete []m_queue;
			m_queue = nullptr;
		}
	}


	//3.push
	bool push(T& pnode)
	{
		m_writeLock.Lock();
		if(m_queue[m_lWritePos] != nullptr)
		{
			m_writeLock.UnLock();
			return false;
		}
			

		m_queue[m_lWritePos] = pnode;

		m_lWritePos = (m_lWritePos + 1)%m_nLen;
		m_writeLock.UnLock();
		return true; 
	}


	//4.pop --从队列中将值取出，移除该节点
	bool pop(T& pNode)
	{
		m_readLock.Lock();
		if(m_queue[m_lReadPos] == nullptr)
		{
			m_readLock.UnLock();
			return false;
		}
		
		pNode = m_queue[m_lReadPos];
		m_queue[m_lReadPos] = nullptr;

		m_lReadPos = (m_lReadPos +1)%m_nLen;
		m_readLock.UnLock();
		return true;
	}

	bool empty()
	{
		if(m_queue[m_lReadPos] == nullptr)
		 {
			 return true;
		 }

		return false;
	}


private:
	T *m_queue;
	long m_lWritePos;
	long m_lReadPos;
	int  m_nLen; 
	CMyLock m_readLock;
	CMyLock m_writeLock;
};





#endif