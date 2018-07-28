#include "stdafx.h"
#include "TCPMediator.h"
#include "0914Disk.h"
#include "DlgMain.h"
TCPMediator::TCPMediator()
{
	m_ptcpNet = new TCPNet(this);
	

	


}

static ProtocolMap m_MapEnter[] =
{
	{_DEF_PROTOCOL_REGISTER_RS,&TCPMediator::RegisterRs},
	{_DEF_PROTOCOL_LOGIN_RS,&TCPMediator::LoginRs},
	{_DEF_PROTOCOL_GETFILELIST_RS,&TCPMediator::GetFileListRs},
	{_DEF_PROTOCOL_UPLOAD_FILE_RS,&TCPMediator::UpLoadFileRs},
	{_DEF_PROTOCOL_UPLOAD_FILEBLOCK_RS,&TCPMediator::UpLoadFileBlockRs},
	/*{_DEF_PROTOCOL_DOWNLOAD_FILE_RQ,&TCPMediator::DownloadFileRq},
	{_DEF_PROTOCOL_TRANSERFER_FILEBLOCK_RS,&TCPMediator::TransferFileRs},*/
	{_DEF_PROTOCOL_SHARELINK_RS,&TCPMediator::ShareLinkRs},
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

void TCPMediator::RegisterRs(char* szbuf,SOCKET sock)
{
	STRU_REGISTERLOGIN_RS *psrr = (STRU_REGISTERLOGIN_RS *)szbuf;
	char *pszbuf = NULL;
	if(psrr->m_lresult == register_fail)
		pszbuf = "register_fail";
	else if(psrr->m_lresult == register_success)
		pszbuf = "register_success";

	AfxMessageBox(pszbuf);
}

void TCPMediator::LoginRs(char* szbuf,SOCKET sock)
{
	STRU_REGISTERLOGIN_RS *psrr = (STRU_REGISTERLOGIN_RS *)szbuf;
	char *pszbuf = NULL;
	if(psrr->m_lresult == login_no_exist)
		pszbuf = "login_no_exist";
	else if(psrr->m_lresult == error_password)
		pszbuf = "error_password";
	else if(psrr->m_lresult == login_success)
	{
		PostMessage(theApp.m_pMainWnd->m_hWnd,UM_LOGINMSG,0,0);
		
		return;
	}
		
	
	AfxMessageBox(pszbuf);
}
void TCPMediator::GetFileListRs(char* szbuf,SOCKET sock)
{
	//��ȡ�ļ��б�Ļظ�
	STRU_GETFILELIST_RS *psgr  = (STRU_GETFILELIST_RS *)szbuf;

	SendMessage(theApp.m_pMainWnd->m_hWnd,UM_GETFILELISTMSG,(WPARAM)psgr->m_aryfile,psgr->m_nFileNum);
	return;
}

void TCPMediator::UpLoadFileRs(char* szbuf,SOCKET  sock)
{
	STRU_UPLOADFILE_RS *psur = (STRU_UPLOADFILE_RS *)szbuf;
	
	
	CDlgMain* pdlg =  (CDlgMain*)(theApp.m_pMainWnd);
	auto ite =pdlg->m_mapFileNameToFileInfo.find(psur->m_szFileName);
	if(ite == pdlg->m_mapFileNameToFileInfo.end())
		return;
	FileUpLoadInfo *pinfo = ite->second;

	if(psur->m_lresult == file_uploadrq_success || psur->m_lresult == file_go_on)
	{
	    if(psur->m_lresult == file_go_on)
			_fseeki64(pinfo->pfile,psur->m_nPos,0);
	
		pinfo->m_llpos = psur->m_nPos;
		//���ļ����ݲ�����
		STRU_UPLOADFILEBLOCK_RQ sur;
		sur.m_nType = _DEF_PROTOCOL_UPLOAD_FILEBLOCK_RQ;
		sur.m_userid = psur->m_userid;

		size_t nRelReadNum = fread_s(sur.m_szFileContent,sizeof(sur.m_szFileContent),sizeof(char),MAX_FILEBLOCK_LEN,pinfo->pfile);
		sur.m_nlen = nRelReadNum;
		sur.m_lFileID = psur->m_lFileID;
		pinfo->m_lfileid = psur->m_lFileID;
		m_ptcpNet->SendData((char*)&sur,sizeof(sur));
		
	
	
	}
	else if(psur->m_lresult == file_uploaded)//�봫
	{
		//�򴰿ڷ���Ϣ--�ļ��ϴ��ɹ�
		fclose(pinfo->pfile);
		//���ļ���Ϣ�����ļ�ӳ�����ɾ��
		//�봰�ڷ���Ϣ
		SendMessage(theApp.m_pMainWnd->m_hWnd,UM_INSERTFILEINFOMSG,(WPARAM)pinfo,0);
		delete pinfo;
		pinfo = NULL;
		pdlg->m_mapFileNameToFileInfo.erase(ite);

	}
	else if(psur->m_lresult == file_upload_rename)
		MessageBox(NULL,"ͬ���ļ�","��ܰ��ʾ",MB_OK);

	return ;
}

void TCPMediator::UpLoadFileBlockRs(char* szbuf,SOCKET sock)
{
	STRU_UPLOADFILEBLOCK_RS *psur = (STRU_UPLOADFILEBLOCK_RS*)szbuf;
	CDlgMain* pdlg =  (CDlgMain*)(theApp.m_pMainWnd);
	auto ite =pdlg->m_mapFileNameToFileInfo.begin();
	FileUpLoadInfo *pinfo = NULL;
	while(ite != pdlg->m_mapFileNameToFileInfo.end())
	{
		if(psur->m_lFileID == ite->second->m_lfileid)
		{
			pinfo = ite->second;
			break;
		}
		ite++;
	}
		
	
	//�ϴ��ļ���ظ�
	switch (psur->m_lresult)
	{
	case fileblock_fail:
		_fseeki64(pinfo->pfile,pinfo->m_llpos,0);
	case fileblock_success:
		{
			if(psur->m_lresult == fileblock_success)
			{
					//�жϵ�û���ļ�β��
			        pinfo->m_llpos += psur->m_nlen;

					if(pinfo->m_llpos == pinfo->m_llfilesize || psur->m_nlen < MAX_FILEBLOCK_LEN)
					{
						fclose(pinfo->pfile);

						//�봰�ڷ���Ϣ
						SendMessage(theApp.m_pMainWnd->m_hWnd,UM_INSERTFILEINFOMSG,(WPARAM)pinfo,0);
						delete pinfo;
						pinfo = NULL;

						

						pdlg->m_mapFileNameToFileInfo.erase(ite);

						return;

					}
			}
		

			//���ļ����ݲ�����
			STRU_UPLOADFILEBLOCK_RQ sur;
			sur.m_nType = _DEF_PROTOCOL_UPLOAD_FILEBLOCK_RQ;
			sur.m_userid = psur->m_userid;

			size_t nRelReadNum = fread_s(sur.m_szFileContent,sizeof(sur.m_szFileContent),sizeof(char),MAX_FILEBLOCK_LEN,pinfo->pfile);
			sur.m_nlen = nRelReadNum;
			sur.m_lFileID = psur->m_lFileID;
		
			m_ptcpNet->SendData((char*)&sur,sizeof(sur));
		}
		break;
	default:
		break;
	}
	
	

}

void TCPMediator::ShareLinkRs(char* szbuf,SOCKET sock)
{
	STRU_SHARELINK_RS *pssr =(STRU_SHARELINK_RS*)szbuf;
	CString str;
	if(pssr->m_lresult == 1)
	{
		str.Format("%lld",pssr->m_linkcode);
		((CDlgMain*)theApp.m_pMainWnd)->m_edtCode.SetWindowText(str);
	}else
	{
		//��ʾ
	}
}




bool TCPMediator::SendData(char *szbuf,int nlen)
{
	if(!m_ptcpNet->SendData(szbuf,nlen))return false;

	return true;
}
 
void TCPMediator::DealData(char* szbuf,SOCKET sock)
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
			(this->*m_MapEnter[i].m_pProtocolMap)(szbuf,sock);
			return;
		}
		i++;
	}
	
}

