

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
	 void RegisterRs(char* szbuf,SOCKET sock); //ע��ظ�
     void LoginRs(char* szbuf,SOCKET sock);  //��¼�ظ�
	 void GetFileListRs(char* szbuf,SOCKET sock); //��ȡ�ļ��б�ظ�
	 void UpLoadFileRs(char* szbuf,SOCKET  sock); //�ϴ��ļ��ظ�
	 void UpLoadFileBlockRs(char* szbuf,SOCKET sock); //�ϴ��ļ���ظ�
//	 void DownloadFileRq(char* szbuf,MySocket *psock); //�����ļ�����
//	 void TransferFileRq(char* szbuf,MySocket *psock,long long userid); //�����ļ�����
//	 void TransferFileRs(char* szbuf,MySocket *psock); //�����ļ�����
	 void ShareLinkRs(char* szbuf,SOCKET sock);
private:
	INet *m_ptcpNet;
	
};

#endif