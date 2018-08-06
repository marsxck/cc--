

#ifndef PACKDEF_H
#define PACKDEF_H
//改变对齐方式
#pragma pack(1)

#define _DEF_PROTOCOL_BASE    2000

#define _DEF_PROTOCOL_REGISTER_RQ     (_DEF_PROTOCOL_BASE + 1)
#define _DEF_PROTOCOL_REGISTER_RS     (_DEF_PROTOCOL_BASE + 2)


#define _DEF_PROTOCOL_LOGIN_RQ		  (_DEF_PROTOCOL_BASE + 3)
#define _DEF_PROTOCOL_LOGIN_RS		  (_DEF_PROTOCOL_BASE + 4)

#define _DEF_PROTOCOL_GETFILELIST_RQ		  (_DEF_PROTOCOL_BASE + 5)
#define _DEF_PROTOCOL_GETFILELIST_RS		  (_DEF_PROTOCOL_BASE + 6)

#define _DEF_PROTOCOL_UPLOAD_FILE_RQ		  (_DEF_PROTOCOL_BASE + 7)
#define _DEF_PROTOCOL_UPLOAD_FILE_RS		  (_DEF_PROTOCOL_BASE + 8)


#define _DEF_PROTOCOL_UPLOAD_FILEBLOCK_RQ		  (_DEF_PROTOCOL_BASE + 9)
#define _DEF_PROTOCOL_UPLOAD_FILEBLOCK_RS		  (_DEF_PROTOCOL_BASE + 10)

#define _DEF_PROTOCOL_DOWNLOAD_FILE_RQ		  (_DEF_PROTOCOL_BASE + 11)
#define _DEF_PROTOCOL_DOWNLOAD_FILE_RS		  (_DEF_PROTOCOL_BASE + 12)


#define _DEF_PROTOCOL_TRANSERFER_FILEBLOCK_RQ		  (_DEF_PROTOCOL_BASE + 13)
#define _DEF_PROTOCOL_TRANSERFER_FILEBLOCK_RS		  (_DEF_PROTOCOL_BASE + 14)

#define _DEF_PROTOCOL_SHARELINK_RQ		  (_DEF_PROTOCOL_BASE + 15)
#define _DEF_PROTOCOL_SHARELINK_RS		  (_DEF_PROTOCOL_BASE + 16)

#define _DEF_PROTOCOL_GETLINK_RQ		  (_DEF_PROTOCOL_BASE + 17)
#define _DEF_PROTOCOL_GETLINK_RS		  (_DEF_PROTOCOL_BASE + 18)

#define _DEF_PROTOCOL_DELETE_FILE_RQ		  (_DEF_PROTOCOL_BASE + 19)
#define _DEF_PROTOCOL_DELETE_FILE_RS		  (_DEF_PROTOCOL_BASE + 20)

#define _DEF_PROTOCOL_ADDFRIEND_RQ		  (_DEF_PROTOCOL_BASE + 21)
#define _DEF_PROTOCOL_ADDFRIEND_RS		  (_DEF_PROTOCOL_BASE + 22)

#define _DEF_PROTOCOL_DELETEFRIEND_RQ		  (_DEF_PROTOCOL_BASE + 23)
#define _DEF_PROTOCOL_DELETEFRIEND_RS		  (_DEF_PROTOCOL_BASE + 24)

#define _DEF_PROTOCOL_PERSONALLETTER_RQ		  (_DEF_PROTOCOL_BASE + 25)
#define _DEF_PROTOCOL_PERSONALLETTER_RS		  (_DEF_PROTOCOL_BASE + 26)

#define _DEF_PROTOCOL_QUIT	  (_DEF_PROTOCOL_BASE + 27)

//
#define MAX_LEN   40
#define MAX_FILELIST_NUM  10
#define MAX_FILEBLOCK_LEN  500
#define MAX_SQL_LEN        200
#define MAX_STHRESH        100*1024*1024
//
#define register_fail    0
#define register_success 1

#define login_no_exist   0
#define error_password   1
#define login_success    2


#define file_upload_rename  0
#define file_uploaded       1
#define file_uploadrq_success 2
#define file_go_on           3

#define fileblock_fail      0 
#define fileblock_success   1



#define file_downloadrq_fail  0
#define file_downloadrq_success  1

//协议包
//注册请求协议\登录请求
typedef int PackType;
struct STRU_REGISTERLOGIN_RQ

{
	 STRU_REGISTERLOGIN_RQ()
	 {
		 m_nType = 0;
		 m_userid = 0;
		 ZeroMemory(m_szpassword,sizeof(m_szpassword));
		 m_lhostip = 0;

	 }
	 PackType  m_nType;
	 long long m_userid;
	 char      m_szpassword[MAX_LEN];
	 long      m_lhostip;

};

struct STRU_REGISTERLOGIN_RS
{
	 STRU_REGISTERLOGIN_RS()
	 {
		 m_nType = 0;
		 m_userid = 0;
		 m_lresult = 0;

	 }
	 PackType  m_nType;
	 long long m_userid;
	 long  m_lresult;
};

//获取文件列表请求
struct STRU_GETFILELIST_RQ
{
	STRU_GETFILELIST_RQ()
	{
		m_nType = _DEF_PROTOCOL_GETFILELIST_RQ;
		m_userid = 0;
	}
	 PackType  m_nType;
	 long long m_userid;
	 
};
//获取文件列表回复

struct FileInfo
{
	 char      m_szFileName[MAX_PATH];
	 long long  m_lFileSize;
	 char      m_szFileUpTime[MAX_LEN];
};

struct STRU_GETFILELIST_RS
{
	STRU_GETFILELIST_RS()
	{
		m_nType = _DEF_PROTOCOL_GETFILELIST_RS;
		m_userid = 0;
		ZeroMemory(m_aryfile,sizeof(m_aryfile));
		m_nFileNum =0;
	}
	 PackType  m_nType;
	 long long m_userid;
	 FileInfo  m_aryfile[MAX_FILELIST_NUM];
	 int       m_nFileNum;
};

//上传文件请求

//_DEF_PROTOCOL_UPLOAD_FILE_RQ


typedef struct STRU_UPLOADFILE_RQ
{
	STRU_UPLOADFILE_RQ()
	{
		m_nType = 0;
		m_userid =0;
		ZeroMemory(m_szFileName,sizeof(m_szFileName));
		m_lFileSize = 0;
		ZeroMemory(m_szFileUpTime,sizeof(m_szFileUpTime));
		ZeroMemory(m_szMD5,sizeof(m_szMD5));
	}
	PackType  m_nType;
	long long m_userid;
	char      m_szFileName[MAX_PATH];
	long long m_lFileSize;
	char      m_szFileUpTime[MAX_LEN];
	char      m_szMD5[MAX_LEN];
}STRU_DOWNLOADFILE_RQ;


typedef struct STRU_UPLOADFILE_RS
{
	STRU_UPLOADFILE_RS()
	{
		m_nType = 0;
		m_userid =0;
		ZeroMemory(m_szFileName,sizeof(m_szFileName));
		m_lFileID = 0;
		m_lresult =0;
	}
	PackType  m_nType;
	long long m_userid;
	char      m_szFileName[MAX_PATH];
	long long m_lFileID;
	long      m_lresult;
	long long m_nPos;
}STRU_DOWNLOADFILE_RS;


//上传文件块_DEF_PROTOCOL_UPLOAD_FILEBLOCK_RQ
typedef struct STRU_UPLOADFILEBLOCK_RQ
{
	STRU_UPLOADFILEBLOCK_RQ()
	{
		m_nType = 0;
		m_userid =0;
		m_lFileID = 0;
		ZeroMemory(m_szFileContent,sizeof(m_szFileContent));
		m_nlen = 0;
	}
	PackType  m_nType;
	long long m_userid;
	long long m_lFileID;
	char      m_szFileContent[MAX_FILEBLOCK_LEN];
	int       m_nlen;

}STRU_TRANSFERFILEBLOCK_RQ;


typedef struct STRU_UPLOADFILEBLOCK_RS
{
	STRU_UPLOADFILEBLOCK_RS()
	{
		m_nType = 0;
		m_userid =0;
		m_lFileID = 0;
		m_lresult = 0;
		m_nlen = 0;
	}
	PackType  m_nType;
	long long m_userid;
	long long m_lFileID;
	long  m_lresult;
	long long m_nlen;

}STRU_TRANSFERFILEBLOCK_RS;


struct STRU_SHARELINK_RQ
{
	STRU_SHARELINK_RQ()
	{
		m_nType = 0;
		m_userid = 0;
		ZeroMemory(m_szFileName,MAX_PATH);
	}
	PackType  m_nType;
	long long m_userid;
	char      m_szFileName[MAX_PATH];

};

struct STRU_SHARELINK_RS
{
	STRU_SHARELINK_RS()
	{
		m_nType = 0;
		m_userid = 0;
		m_linkcode = 0;
	}
	PackType  m_nType;
	long long m_userid;
	long long m_linkcode;
	long long m_lresult;

};





#endif
