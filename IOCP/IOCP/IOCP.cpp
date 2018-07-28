#include "IOCP.h"


IOCP::IOCP()
{
	m_sock = NULL;
	m_nProcessorNum = 0;
	m_hIOCP = NULL;
	m_bFlagQuit = TRUE;
}


IOCP::~IOCP(void)
{
}

bool IOCP::InitNetWork()
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


	m_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_sock)
	{
		UnInitNetWork();
		return false;
	}
	sockaddr_in  addr;
	//本机环网127.0.0.1
	//InetPton(AF_INET,L"192.168.1.251",(void*)&addr.sin_addr.S_un.S_addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY/*GetValidIp()*/;
	addr.sin_port = htons(_DEF_PORT);
	if (SOCKET_ERROR == bind(m_sock, (const sockaddr*)&addr, sizeof(addr)))
	{
		UnInitNetWork();
		return false;

	}
	//获得cpu个数
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	m_nProcessorNum = si.dwNumberOfProcessors * 2;
	if (SOCKET_ERROR == listen(m_sock, m_nProcessorNum))
	{
		UnInitNetWork();
		return false;
	}

	//创建完成端口
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (m_hIOCP == NULL)
	{
		UnInitNetWork();
		return false;
	}
	//将m_sock 交给完成端口管
	CreateIoCompletionPort((HANDLE)m_sock, m_hIOCP, m_sock, 0);

	//投递接收连接的请求
	for (int i = 0; i<m_nProcessorNum; i++)
	{
		if (!PostAccept())
		{
			continue;
		}
	}

	//观察完成端口的状态
	for (int i = 0; i < m_nProcessorNum; i++)
	{
		HANDLE hThread = (HANDLE)_beginthreadex(0, 0, &ThreadProc, this, 0, 0);
		if (hThread)
		{
			m_lstThread.push_back(hThread);
		}
	}




	return true;
}

unsigned _stdcall IOCP::ThreadProc(void * lpvoid)
{
	IOCP *pthis = (IOCP*)lpvoid;
	DWORD dwNumberOfBytes;
	SOCKET sock;
	MySocket *pSocket = NULL;
	BOOL  bflag;
	while (pthis->m_bFlagQuit)
	{
		//观察完成端口的状态
		bflag = GetQueuedCompletionStatus(pthis ->m_hIOCP, &dwNumberOfBytes, (PULONG_PTR)&sock, (LPOVERLAPPED *)&pSocket, INFINITE);
		if (!bflag)
		{
			//判断谁下线拉
			auto ite = pthis->m_lstMySocket.begin();
			while (ite != pthis->m_lstMySocket.end())
			{
				if (*ite == pSocket)
				{
					WSACloseEvent((*ite)->m_olp.hEvent);
					closesocket((*ite)->m_sock);
					delete pSocket;
					pSocket = NULL;
				}
			}
			continue;
		}

		if (sock && pSocket)
		{
			switch (pSocket->m_nType)
			{
			case NT_ACCEPT: //接收
			{
				//获得客户端的ip jiang ip -- pSocket
				//投递接收数据的请求
				pthis->PostRecv(pSocket);

				//投递接收连接的请求
				pthis->PostAccept();

				//将waiter 交给完成端口管理
				CreateIoCompletionPort((HANDLE)pSocket->m_sock, pthis->m_hIOCP, pSocket->m_sock, 0);
			}
			break;
			case NT_READ:
				//处理数据
				//pSocket->m_szbuf;
				pSocket->m_szbuf;
				pthis->PostRecv(pSocket);
				break;
			default:
				break;
			}
		}

	}
	return 0;
}


bool IOCP::PostRecv(MySocket *pSocket)
{
	DWORD dwNumberOfBytesRecvd;
	DWORD dwFlags = false;
	WSABUF wb;
	wb.buf = pSocket->m_szbuf;
	wb.len = sizeof(pSocket->m_szbuf);
	pSocket->m_nType = NT_READ;

	if (WSARecv(pSocket->m_sock, &wb, 1, &dwNumberOfBytesRecvd, &dwFlags, &pSocket->m_olp,
		NULL))
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return true;
}

bool IOCP::PostAccept()
{
	DWORD dwBytesReceived;

	MySocket *pSocket = new MySocket;
	pSocket->m_nType = NT_ACCEPT;
	pSocket->m_olp.hEvent = WSACreateEvent();
	pSocket->m_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (!AcceptEx(m_sock, pSocket->m_sock,pSocket->m_szbuf, 0, sizeof(sockaddr_in) + 16,
		sizeof(sockaddr_in) + 16, &dwBytesReceived, &pSocket->m_olp))
	{

		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			WSACloseEvent(pSocket->m_olp.hEvent);
			closesocket(pSocket->m_sock);
			delete pSocket;
			pSocket = NULL;
			return false;
		}
	}
	m_lstMySocket.push_back(pSocket);
	return true;
}

void IOCP::UnInitNetWork()
{
	m_bFlagQuit = FALSE;
	int i = m_nProcessorNum;
	while (i-- >0)
	{
		PostQueuedCompletionStatus(m_hIOCP, NULL, NULL, NULL);
	}


	WSACleanup();
	if (m_sock)
	{

		closesocket(m_sock);
		m_sock = NULL;
	}
	if (m_hIOCP)
	{
		CloseHandle(m_hIOCP);
		m_hIOCP = NULL;
	}


	auto ite = m_lstThread.begin();
	while (ite != m_lstThread.end())
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(*ite, 100))
		{
			TerminateThread(*ite, -1);
		}
		CloseHandle(*ite);
		*ite = NULL;

		ite++;
	}

	auto iteSock = m_lstMySocket.begin();
	while (iteSock != m_lstMySocket.end())
	{
		WSACloseEvent((*iteSock)->m_olp.hEvent);
		closesocket((*iteSock)->m_sock);
		delete (*iteSock);
		(*iteSock) = NULL;

		iteSock++;
	}

}

bool IOCP::SendData(MySocket *pSocket, char *szbuf, int nlen)
{
	if (!pSocket || !szbuf || nlen <= 0)return false;
	//发送包大小
	if (send(pSocket->m_sock, (const char*)&nlen, sizeof(int), 0) <= 0)
	{
		return false;
	}
	//发送包数据
	if (send(pSocket->m_sock, szbuf, nlen, 0) <= 0)
	{
		return false;
	}
	return true;
}