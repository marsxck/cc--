#include "stdafx.h"
#include "TCPNet.h"

TCPNet::TCPNet(IMediator *pMediator)
{
	m_sockClient = NULL;
	m_hThread = NULL;
	m_bflagQuit = true;
	m_pMediator = pMediator;
}

TCPNet::~TCPNet()
{}

 bool TCPNet::InitNetWork()
 {
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;


    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
     
      
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
       
       
       UnInitNetWork();
        return false;
    }
   

	m_sockClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(INVALID_SOCKET == m_sockClient)
	{
		UnInitNetWork();
		return false;
	}
	sockaddr_in  addr;
	InetPton(AF_INET,SERVERIP,(void*)&addr.sin_addr.S_un.S_addr);
	addr.sin_family = AF_INET;
	//addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.251");
	addr.sin_port = htons(_DEF_PORT);
	 
	if(SOCKET_ERROR ==	connect(m_sockClient,(const sockaddr*)&addr,sizeof(addr)))
	{
		UnInitNetWork();
		return false;
	}

	//创建线程
	m_hThread  = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,0);
	return true;
 }

 unsigned _stdcall TCPNet::ThreadProc(void * lpvoid)
 {
	 TCPNet *pthis = (TCPNet *)lpvoid;
	 char *pszbuf = NULL;
	 int nPackSize;
	 int nRelReadNum;
	 int nTempSize;
	 int nOffset = 0;
	 while(pthis->m_bflagQuit)
	 {
		 //recv ---包大小
		  nRelReadNum = recv(pthis->m_sockClient,(char*)&nPackSize,sizeof(int),0);
		  if(nRelReadNum <=0)continue;

		  nTempSize = nPackSize;
		  pszbuf = new char[nPackSize];
		  nOffset = 0;
		 //recv --包
		 
		 while(nTempSize)
		 {
			 nRelReadNum = recv(pthis->m_sockClient,pszbuf+nOffset,nTempSize,0);
			 nTempSize -= nRelReadNum;
			 nOffset += nRelReadNum;

		 }
		 //交给中介者处理
		 pthis->m_pMediator->DealData(pszbuf,pthis->m_sockClient);
		 delete []pszbuf;
		 pszbuf = NULL;
	 }
	 return 0;
 }

 void TCPNet::UnInitNetWork()
 {
	  WSACleanup();
	  if(m_sockClient)
	  {
		  closesocket(m_sockClient);
		  m_sockClient = NULL;
	  }

	  m_bflagQuit = false;
	  if(m_hThread)
	  {
		  if(WAIT_TIMEOUT == WaitForSingleObject(m_hThread,100))
			  TerminateThread(m_hThread,-1);

		  CloseHandle(m_hThread);
		  m_hThread = NULL;
	  }
 }

 bool TCPNet::SendData(char *szbuf,int nlen)
 {
	 if(send(m_sockClient,szbuf,nlen,0) <=0)return false;
	 return true;
 }