

#ifndef TCPMEDIATOR_H
#define TCPMEDIATOR_H


#include "IOCP.h"
#include "CMySql.h"
#include "IMediator.h"
#include <time.h>
#include <map>
using namespace std;
class TCPMediator;
typedef void (TCPMediator:: *PFUN)(char*,MySocket* );
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
	 void DealData(char* szbuf,MySocket *psock);
public:
	 void RegisterRq(char* szbuf,MySocket *psock); //ע������
	 void LoginRq(char* szbuf,MySocket *psock);  //��¼����
	 void GetFileListRq(char* szbuf,MySocket *psock); //��ȡ�ļ��б�����
	 void UpLoadFileRq(char* szbuf,MySocket *psock); //�ϴ��ļ�����
	 void UpLoadFileBlockRq(char* szbuf,MySocket *psock); //�ϴ��ļ�������
	 void DownloadFileRq(char* szbuf,MySocket *psock); //�����ļ�����
	 void TransferFileRq(char* szbuf,MySocket *psock,long long userid); //�����ļ�����
	 void TransferFileRs(char* szbuf,MySocket *psock); //�����ļ�����
	 void ShareLinkRq(char* szbuf,MySocket *psock);
private:
	INet *m_ptcpNet;
	CMySql m_sql;
	TCHAR m_szSystemPath[MAX_PATH];
public:

size_t SDBMHash(const char *str)  
{  
    register size_t hash = 0;  
    while (size_t ch = (size_t)*str++)  
    {  
        hash = 65599 * hash + ch;         
    }  
    return hash;  
}  

long long GetFileID(const char*str)
{
	size_t hash = SDBMHash(str);
	 long long lltime =  (long long)GetCurrentTime();

	 return hash + lltime;
}


long long GetCode(long long fileid)
{
	long long lltime =  (long long)GetCurrentTime();

	return lltime + fileid;
}

typedef struct FileUpLoadInfo
{
	FILE *pfile;
	long long m_lfileid;
	long long m_llpos;
	long long m_llfilesize;
	char m_szFileName[MAX_PATH];

}FileDownloadInfo;

map<long long, FileUpLoadInfo*>  m_mapUpLoadFileIdToFileInfo;

map<long long, FileUpLoadInfo*>  m_mapDownLoadFileIdToFileInfo;
};

#endif