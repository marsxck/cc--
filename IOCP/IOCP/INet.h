#pragma once

#include <Winsock2.h>
#include <process.h>

#pragma comment(lib,"Ws2_32.lib")

struct MySocket;
class INet
{
public:
	INet() {};
	virtual ~INet() {};
public:
	virtual bool InitNetWork() = 0;  //加载库  创建socket  bind listen 
	virtual void UnInitNetWork() = 0;
	virtual bool SendData(MySocket *psock, char *szbuf, int nlen) = 0;
public:
	static long GetValidIp()
	{
		char szname[100] = { 0 };
		long lip;
		struct in_addr addr;

		//获得本机名
		if (!gethostname(szname, sizeof(szname)))
		{
			//获得本机iplist
			struct hostent* remoteHost = gethostbyname(szname);

			if (remoteHost->h_addr_list[0] != 0)
			{
				addr.s_addr = *(u_long *)remoteHost->h_addr_list[0];
				//printf("\tIPv4 Address #%d: %s\n", i, inet_ntoa(addr));
				lip = addr.s_addr;
			}



		}
		return lip;
	}
};