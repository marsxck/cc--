
#include "TCPMediator.h"

TCPMediator::TCPMediator()
{
	m_ptcpNet = new IOCP(this);
	

	memcpy(m_szSystemPath,"F:/disk/",sizeof(m_szSystemPath));


}

static ProtocolMap m_MapEnter[] =
{
	{_DEF_PROTOCOL_REGISTER_RQ,&TCPMediator::RegisterRq},
	{_DEF_PROTOCOL_LOGIN_RQ,&TCPMediator::LoginRq},
	{_DEF_PROTOCOL_GETFILELIST_RQ,&TCPMediator::GetFileListRq},
	{_DEF_PROTOCOL_UPLOAD_FILE_RQ,&TCPMediator::UpLoadFileRq},
	{_DEF_PROTOCOL_UPLOAD_FILEBLOCK_RQ,&TCPMediator::UpLoadFileBlockRq},
	{_DEF_PROTOCOL_DOWNLOAD_FILE_RQ,&TCPMediator::DownloadFileRq},
	{_DEF_PROTOCOL_TRANSERFER_FILEBLOCK_RS,&TCPMediator::TransferFileRs},
	{_DEF_PROTOCOL_SHARELINK_RQ,&TCPMediator::ShareLinkRq},
	{0,0}
};



TCPMediator::~TCPMediator()
{
	  if(m_ptcpNet)
	  {
		 
		  delete m_ptcpNet;
		  m_ptcpNet = nullptr;
	  }
}


bool TCPMediator::open() 
{

	if(!m_sql.ConnectMySql("localhost","root","a8494552","disk"))
	{
		return false;
	}
	if(!m_ptcpNet->InitNetWork())
	{
		return false;
	}
	
	return true;
}
void TCPMediator::close()
{
	
	m_ptcpNet->UnInitNetWork();
}

 void TCPMediator::RegisterRq(char* szbuf,MySocket *psock)
 {
	 //ע������
	 STRU_REGISTERLOGIN_RQ *psrr = (STRU_REGISTERLOGIN_RQ *)szbuf;
	 STRU_REGISTERLOGIN_RS srr;
	 srr.m_nType = _DEF_PROTOCOL_REGISTER_RS;   
	 srr.m_userid = psrr->m_userid;
	 srr.m_lresult = register_fail;
	 //���
	 char  szsql[MAX_SQL_LEN] = {0};
	 list<string> lststr;
	 sprintf(szsql,"select t_userid from t_user where t_userid = %lld",psrr->m_userid);
	 
	 m_sql.SelectMySql(szsql,1,lststr);

	 if(lststr.size() ==  0)
	 {
		 srr.m_lresult = register_success;
		 //����Ϣд�����ݿ�

		 sprintf(szsql,"insert into t_user values(%lld,'%s')",psrr->m_userid,psrr->m_szpassword);

		 m_sql.UpdateMySql(szsql);

		 //����Ŀ¼
		 char szpath[MAX_PATH] = {0};
		 sprintf(szpath,"%s%lld",m_szSystemPath,psrr->m_userid);
		 BOOL bflag =  CreateDirectory(szpath,NULL);
		 
	 }

	 m_ptcpNet->SendData(psock,(char*)&srr,sizeof(srr));

 }

void TCPMediator::LoginRq(char* szbuf,MySocket *psock)
{
	//��¼����
	STRU_REGISTERLOGIN_RQ *psrr=(STRU_REGISTERLOGIN_RQ *)szbuf;
	STRU_REGISTERLOGIN_RS srr;
	srr.m_nType = _DEF_PROTOCOL_LOGIN_RS;
	srr.m_userid = psrr->m_userid;
	
	char szsql[MAX_SQL_LEN] = {0};
	list<string> lststr;
	sprintf(szsql,"select t_userpassword from t_user where t_userid = %lld",psrr->m_userid);
	
	m_sql.SelectMySql(szsql,1,lststr);

	//�ж��û��Ƿ����
	if(lststr.size() == 0 )
	{
		srr.m_lresult = login_no_exist;
	}
	else
	{
		srr.m_lresult = login_success;
		string strpassword = lststr.front();
		lststr.pop_front();
		//У������
		if(0 != strcmp(strpassword.c_str(),psrr->m_szpassword))
		{
			srr.m_lresult = error_password;
		}

	}
	

	
	 m_ptcpNet->SendData(psock,(char*)&srr,sizeof(srr));



}

void TCPMediator::GetFileListRq(char* szbuf,MySocket *psock)
{
	//��ȡ�ļ��б������
	STRU_GETFILELIST_RQ *psgr = (STRU_GETFILELIST_RQ *)szbuf;
	STRU_GETFILELIST_RS sgr;
	sgr.m_nType = _DEF_PROTOCOL_GETFILELIST_RS;
	sgr.m_userid = psgr->m_userid;
	

	char szsql[MAX_SQL_LEN] = {0};
	list<string> lststr;
	sprintf(szsql,"select t_filename,t_filesize,t_fileuptime from t_file \
 inner join t_user_file on t_file.t_fileid = t_user_file.t_fileid \
 where t_userid =%lld",psgr->m_userid);
	m_sql.SelectMySql(szsql,3,lststr);

	
	
	while(lststr.size() >0)
	{
		string strfilename = lststr.front();
		lststr.pop_front();
		string strfilesize = lststr.front();
		lststr.pop_front();
		string strfileuptime = lststr.front();
		lststr.pop_front();

		strcpy_s(sgr.m_aryfile[sgr.m_nFileNum].m_szFileName,sizeof(sgr.m_aryfile[sgr.m_nFileNum].m_szFileName),strfilename.c_str());
		strcpy_s(sgr.m_aryfile[sgr.m_nFileNum].m_szFileUpTime,sizeof(sgr.m_aryfile[sgr.m_nFileNum].m_szFileUpTime),strfileuptime.c_str());
		sgr.m_aryfile[sgr.m_nFileNum].m_lFileSize = _atoi64(strfilesize.c_str());
		sgr.m_nFileNum++;

		if(sgr.m_nFileNum == MAX_FILELIST_NUM)
		{
			 m_ptcpNet->SendData(psock,(char*)&sgr,sizeof(sgr));
			 sgr.m_nFileNum = 0;
		}
	}
	
	if(sgr.m_nFileNum > 0)
	{
		 m_ptcpNet->SendData(psock,(char*)&sgr,sizeof(sgr));
	}

}


void TCPMediator::UpLoadFileRq(char* szbuf,MySocket *psock)
{
	STRU_UPLOADFILE_RQ *psur = (STRU_UPLOADFILE_RQ *)szbuf;
	STRU_UPLOADFILE_RS sur;
	sur.m_userid = psur->m_userid;
	memcpy(sur.m_szFileName,psur->m_szFileName,sizeof(sur.m_szFileName));
	sur.m_nType = _DEF_PROTOCOL_UPLOAD_FILE_RS;
	sur.m_nPos = 0;
	char szsql[MAX_SQL_LEN] = {0};
	list<string> lststr;
	//�ж��Լ���û����ͬ���ļ�
	sprintf(szsql," select t_file.t_fileid from t_file \
 inner join t_user_file on t_file.t_fileid = t_user_file.t_fileid \
 where t_userid = %lld and t_filename = '%s' ",psur->m_userid,psur->m_szFileName);

	m_sql.SelectMySql(szsql,1,lststr); 
	
	//1.����ͬ���ļ�
	if(lststr.size() >0)
	{
		string strfileid = lststr.front();
		lststr.pop_front();

		sur.m_lresult = file_upload_rename;

		//�жϵ�ǰ�ǲ��Ƕϵ�����
		auto ite = m_mapUpLoadFileIdToFileInfo.find(_atoi64(strfileid.c_str()));
		if(ite != m_mapUpLoadFileIdToFileInfo.end())
		{
			sur.m_lFileID = _atoi64(strfileid.c_str());
			sur.m_lresult = file_go_on;
			sur.m_nPos = ite->second->m_llpos;
		}
		

	}
	else 
	{
		sur.m_lresult = file_uploadrq_success;
		//2.��������
		//�жϵ�ǰ�ļ��Ĵ�С---���������ֵ�����ж��ļ�ָ���Ƿ�ƥ��100M
		list<string > lstfile;
		 if(psur->m_lFileSize > MAX_STHRESH)
		 {
			 sprintf(szsql," select t_fileid,t_filecount from t_file where t_fileMD5 = '%s'",psur->m_szMD5);

			 m_sql.SelectMySql(szsql,2,lstfile);

			 if(lstfile.size() > 0 )
			 {
				 sur.m_lresult = file_uploaded;
				 string strfileid = lstfile.front();
				 lstfile.pop_front();
				 string strfilecount = lstfile.front();
				 lstfile.pop_front();

				 long long fileid =  _atoi64(strfileid.c_str());
				 long long filecount =  _atoi64(strfilecount.c_str());
				 //���ļ�ӳ�䵽��ǰ�û���
				 sprintf(szsql,"insert into t_user_file(t_userid,t_fileid) values(%lld,%lld)",psur->m_userid,fileid);
				 m_sql.UpdateMySql(szsql);
				 filecount++;
				 sprintf(szsql," update t_file set t_filecount = %lld where t_fileid =%lld ",filecount,fileid);
				 m_sql.UpdateMySql(szsql);

				 //֪ͨ�û��ϴ��ɹ�


			 }
			

		 }

	}
	
	//3.��û�д���
	if(sur.m_lresult == file_uploadrq_success)
	{
		
		//�����ļ�
		int a;
		FILE *pfile = NULL;
		char szfilename[MAX_PATH] = {0};
		char szfilpath[MAX_PATH] = { 0 };
		sprintf(szfilpath,"%s%lld",m_szSystemPath,psur->m_userid);
		CreateDirectory(szfilpath,NULL);
		sprintf(szfilename, "%s%lld/%s", m_szSystemPath, psur->m_userid, psur->m_szFileName);
		fopen_s(&pfile,szfilename,"wb");
		a = GetLastError();

		long long fileid = GetFileID(psur->m_szFileName);

		//���ļ�д�뵽���ݿ���
		sprintf(szsql,"insert into t_file values(%lld,'%s',%lld,'%s','%s','%s',%d)",fileid,psur->m_szFileName,0,
			     szfilename,psur->m_szFileUpTime,psur->m_szMD5,1);
		m_sql.UpdateMySql(szsql);
		//���ļ����û�ӳ��д�뵽���ݿ���
		//char szsql[MAX_SQL_LEN] = {0};
		sprintf(szsql,"insert into t_user_file(t_userid,t_fileid) values(%lld,%lld)"
				          ,psur->m_userid,fileid);
		m_sql.UpdateMySql(szsql);
		// ---file fileid, npos,filename, filesize
		FileUpLoadInfo *pInfo = new FileUpLoadInfo;
		pInfo->pfile = pfile;
		pInfo->m_lfileid = fileid;
		pInfo->m_llpos = 0;
		pInfo->m_llfilesize = psur->m_lFileSize;
		memcpy(pInfo->m_szFileName,psur->m_szFileName,sizeof(pInfo->m_szFileName));


		m_mapUpLoadFileIdToFileInfo[fileid] = pInfo;
		sur.m_lFileID = fileid;
	}



	m_ptcpNet->SendData(psock,(char*)&sur,sizeof(sur));


}


void TCPMediator::UpLoadFileBlockRq(char* szbuf,MySocket *psock)
{
	STRU_UPLOADFILEBLOCK_RQ *psur = (STRU_UPLOADFILEBLOCK_RQ *)szbuf;
	//�ϴ��ļ�������
	STRU_UPLOADFILEBLOCK_RS sur;
	sur.m_lFileID = psur->m_lFileID;
	sur.m_nType = _DEF_PROTOCOL_UPLOAD_FILEBLOCK_RS;
	sur.m_userid = psur->m_userid;
	sur.m_lresult = fileblock_fail;
	//ͨ���ļ�ID --- �ļ���Ϣ�ṹ
	auto ite = m_mapUpLoadFileIdToFileInfo.find(psur->m_lFileID);
	if(ite != m_mapUpLoadFileIdToFileInfo.end())
	{
		sur.m_lresult = fileblock_success;
		//���ļ���д������
		size_t nrelWriteNum = fwrite(psur->m_szFileContent,sizeof(char),psur->m_nlen,ite->second->pfile);
		sur.m_nlen = nrelWriteNum;
		ite->second->m_llpos += nrelWriteNum;

		//�ж��Ƿ��ļ�β
		if(ite->second->m_llfilesize ==ite->second->m_llpos || psur->m_nlen < MAX_FILEBLOCK_LEN )
		{
			fclose(ite->second->pfile);

			////���ļ����û�ӳ��д�뵽���ݿ���
			char szsql[MAX_SQL_LEN] = {0};
			//sprintf(szsql,"insert into t_user_file(t_userid,t_fileid) values(%lld,%lld)"
			//	          ,psur->m_userid,psur->m_lFileID);
			//m_sql.UpdateMySql(szsql);

			//�����ļ���С���ϴ�ʱ��-�����ݿ���
			sprintf(szsql,"update t_file set t_filesize = %lld  where t_fileid = %lld",ite->second->m_llfilesize,ite->second->m_lfileid);
			m_sql.UpdateMySql(szsql);


			delete ite->second;
			m_mapUpLoadFileIdToFileInfo.erase(ite);


		}

	}

	
	m_ptcpNet->SendData(psock,(char*)&sur,sizeof(sur));
}



void TCPMediator::DownloadFileRq(char* szbuf,MySocket *psock)
{
	//�����ļ�����
	STRU_DOWNLOADFILE_RQ *psdr = (STRU_DOWNLOADFILE_RQ *)szbuf;
	STRU_DOWNLOADFILE_RS sdr;
	sdr.m_nType = _DEF_PROTOCOL_DOWNLOAD_FILE_RS;
	sdr.m_userid = psdr->m_userid;
	memcpy(sdr.m_szFileName,psdr->m_szFileName,sizeof(sdr.m_szFileName));
	sdr.m_lresult = file_downloadrq_fail;
	FileDownloadInfo *pInfo = NULL;
	//�����ļ�
	char szsql[MAX_SQL_LEN] = {0};
	list<string> lstfile;
	sprintf(szsql,"select t_fileid,t_filepath,t_filesize from t_file  \
inner join t_user_file on t_file.t_fileid = t_user_file.t_fileid \
where t_userid = %lld and t_filename = '%s' ",psdr->m_userid,psdr->m_szFileName);

	m_sql.SelectMySql(szsql,3,lstfile);
	if(lstfile.size() >0)
	{
		string strfileid = lstfile.front();
		lstfile.pop_front();
		string strfilepath = lstfile.front();
		lstfile.pop_front();
		string strfilesize = lstfile.front();
		lstfile.pop_front();
		
		sdr.m_lFileID = _atoi64(strfileid.c_str());
		sdr.m_lresult = file_downloadrq_success;
		sdr.m_nPos = 0;

		//��ֻ������ʽ���ļ�
		FILE *pfile = NULL;
		fopen_s(&pfile,strfilepath.c_str(),"rb");
		
		pInfo = new FileDownloadInfo;
		pInfo->m_lfileid = sdr.m_lFileID;
		pInfo->m_llfilesize = _atoi64(strfilesize.c_str());
		pInfo->m_llpos = 0;
		pInfo->pfile = pfile;
		memcpy(pInfo->m_szFileName,psdr->m_szFileName,sizeof(pInfo->m_szFileName));
		
		m_mapDownLoadFileIdToFileInfo[pInfo->m_lfileid] = pInfo;
	}
	


	m_ptcpNet->SendData(psock,(char*)&sdr,sizeof(sdr));

	//�����ǰfile_downloadrq_success 
	if(sdr.m_lresult == file_downloadrq_success)
	{
		//���ļ��鲢����
		TransferFileRq((char*)pInfo,psock,psdr->m_userid);
	}
	



}



void TCPMediator::TransferFileRq(char* szbuf,MySocket *psock,long long userid)
{
	FileDownloadInfo *pInfo = (FileDownloadInfo*)szbuf;
	STRU_TRANSFERFILEBLOCK_RQ str;
	str.m_lFileID = pInfo->m_lfileid;
	str.m_nType = _DEF_PROTOCOL_TRANSERFER_FILEBLOCK_RQ;
	str.m_userid = userid;

	//���ļ����ݲ�����
	size_t nRelReadNum =(size_t)fread(str.m_szFileContent,sizeof(char),sizeof(str.m_szFileContent),pInfo->pfile);
	str.m_nlen = (int)nRelReadNum;


	m_ptcpNet->SendData(psock,(char*)&str,sizeof(str));
}

void TCPMediator::TransferFileRs(char* szbuf,MySocket *psock)
{
	//�����ļ���ظ�
	STRU_TRANSFERFILEBLOCK_RS *pstr = (STRU_TRANSFERFILEBLOCK_RS *)szbuf;
	STRU_TRANSFERFILEBLOCK_RQ str;
	str.m_lFileID = pstr->m_lFileID;
	str.m_nType = _DEF_PROTOCOL_TRANSERFER_FILEBLOCK_RQ;
	str.m_userid = pstr->m_userid;
	auto ite = m_mapDownLoadFileIdToFileInfo.find(pstr->m_lFileID);
	FileDownloadInfo *pInfo = ite->second;
	//�жϴ����ļ��ɹ�����ʧ��
	if(pstr->m_lresult == fileblock_fail)
	{
		 //�ش�
		//�ƶ��ļ�ָ��--- npos
		_fseeki64(pInfo->pfile,pInfo->m_llpos,0);

		

	}
	else if(pstr->m_lresult == fileblock_success)
	{
		pInfo->m_llpos += pstr->m_nlen;

		//�ж��Ƿ��ļ�β
		if(pInfo->m_llpos == pInfo->m_llfilesize || pstr->m_nlen < MAX_FILEBLOCK_LEN)
		{
			//�ر��ļ�---ɾ��ӳ��
			fclose(pInfo->pfile);

			delete pInfo;
			pInfo = NULL;
			m_mapDownLoadFileIdToFileInfo.erase(ite);

			return;
		}

	
	
	}

	size_t nRelReadNum =(size_t)fread(str.m_szFileContent,sizeof(char),sizeof(str.m_szFileContent),pInfo->pfile);
	str.m_nlen = (int)nRelReadNum;

	m_ptcpNet->SendData(psock,(char*)&str,sizeof(str));

}

void TCPMediator::ShareLinkRq(char* szbuf,MySocket *psock)
{
	//�жϵ�ǰ�ļ���û��û�д��꣬���û�д��������򷵻�ʧ��

	//������������
	STRU_SHARELINK_RS ssr;
	STRU_SHARELINK_RQ *psrr = (STRU_SHARELINK_RQ *)szbuf;
	ssr.m_nType = _DEF_PROTOCOL_SHARELINK_RS;
	ssr.m_userid = psrr->m_userid;
	ssr.m_lresult = 0;
	//ͨ���ļ������ҵ��ļ�ID 
	char szsql[MAX_SQL_LEN] = {0};
	list<string> lststr;
	sprintf(szsql,"select  t_file.t_fileid from t_file  \
inner join t_user_file on t_file.t_fileid = t_user_file.t_fileid \
where t_filename = '%s' and t_userid = %lld",psrr->m_szFileName,psrr->m_userid);

	m_sql.SelectMySql(szsql,1,lststr);
	 
	if(lststr.size() >0)
	{
		string strfileid = lststr.front();
		lststr.pop_front();

		//����code 
		long long code = GetCode(_atoi64(strfileid.c_str()));
		ssr.m_linkcode = code;
		ssr.m_lresult = 1;
		sprintf(szsql,"insert into t_user_share_file(t_userid,t_fileid,t_code) values(%lld,%lld,%lld);",
			psrr->m_userid,_atoi64(strfileid.c_str()),code);
		m_sql.UpdateMySql(szsql);
	}


	m_ptcpNet->SendData(psock,(char*)&ssr,sizeof(ssr));

}



void TCPMediator::DealData(char* szbuf,MySocket *psock)
{
	//��������
	int *ptype =(int*)szbuf;
	int i = 0;
	while(1)
	{
		if(m_MapEnter[i].m_nProtocol == 0)
		{
			break;
		}
		else if(m_MapEnter[i].m_nProtocol == *ptype)
		{
			(this->*m_MapEnter[i].m_pProtocolMap)(szbuf,psock);
			return;
		}
		i++;
	}
	
}

