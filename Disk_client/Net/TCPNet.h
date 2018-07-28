#pragma once
#ifndef TCPNET_H
#define TCPNET_H
#include "INet.h"
#include "IMediator.h"
#include <Ws2tcpip.h>


class TCPNet:public  INet
{
public:
	TCPNet(IMediator *pMediator);
	virtual ~TCPNet();
public:
	virtual bool InitNetWork();  //º”‘ÿø‚  ¥¥Ω®socket  bind listen 
	virtual void UnInitNetWork();
	virtual bool SendData( char *szbuf,int nlen);
	static unsigned _stdcall ThreadProc(void * );
private:
	SOCKET m_sockClient;
	HANDLE  m_hThread;
	bool    m_bflagQuit;
	IMediator *m_pMediator;
};





#endif