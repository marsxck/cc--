#pragma once

#include "INet.h"
#include "IMediator.h"
#include <Ws2tcpip.h>
#include <Mswsock.h>
#include <list>
using namespace std;
#define _DEF_PORT  1234
#define _DEF_SIZE  1024

#pragma comment(lib,"Mswsock.lib")

enum NetType{NT_UNKOWN,NT_ACCEPT,NT_READ,NT_WRITE,NT_CLOSE};

struct MySocket
{
	MySocket()
	{
		m_olp.hEvent = NULL;
		m_sock = NULL;
		m_nType = NT_UNKOWN;
		ZeroMemory(m_szbuf,sizeof(m_szbuf));
	}
	OVERLAPPED m_olp;  //�ص�io�¼�
	SOCKET     m_sock; //���������¼���socket
	NetType    m_nType; //�����¼�
	char       m_szbuf[_DEF_SIZE];//������


};





class IOCP :public INet
{
public:
	IOCP(IMediator *pMediator);
	~IOCP(void);
public:
	 bool InitNetWork();  //���ؿ�  ����socket  bind listen 
	 void UnInitNetWork();
	 bool SendData(MySocket *pSocket,char *szbuf,int nlen);
public:
	bool PostAccept();
	bool PostRecv(MySocket *pSocket);
	static   unsigned _stdcall ThreadProc( void * );

private:
	
	SOCKET m_sock;
	bool   m_bFlagQuit;
	int   m_nProcessorNum;
	HANDLE  m_hIOCP;
	list<HANDLE >  m_lstThread;
	list<MySocket*>  m_lstMySocket;
	IMediator *m_pMediator;
};
