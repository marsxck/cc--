

#ifndef TCPMEDIATOR_H
#define TCPMEDIATOR_H


#include "TCPNet.h"

#include "IMediator.h"

class TCPMediator;
typedef void (TCPMediator:: *PFUN)(char*,SOCKET );
struct ProtocolMap
{
	int m_nProtocol;
	PFUN m_pProtocolMap;
};

class TCPMediator :public IMediator
{
public:
	TCPMediator();
	virtual~TCPMediator();
public:
	 bool open() ;
	 void close();
	 void DealData(char* szbuf,SOCKET sock);
	 bool SendData(char *szbuf,int nlen);
//public:
	 void RegisterRs(char* szbuf,SOCKET sock); //注册回复
     void LoginRs(char* szbuf,SOCKET sock);  //登录回复
	 void GetFileListRs(char* szbuf,SOCKET sock); //获取文件列表回复
	 void UpLoadFileRs(char* szbuf,SOCKET  sock); //上传文件回复
	 void UpLoadFileBlockRs(char* szbuf,SOCKET sock); //上传文件块回复
//	 void DownloadFileRq(char* szbuf,MySocket *psock); //下载文件请求
//	 void TransferFileRq(char* szbuf,MySocket *psock,long long userid); //传输文件请求
//	 void TransferFileRs(char* szbuf,MySocket *psock); //传输文件请求
	 void ShareLinkRs(char* szbuf,SOCKET sock);
private:
	INet *m_ptcpNet;
	
};

#endif