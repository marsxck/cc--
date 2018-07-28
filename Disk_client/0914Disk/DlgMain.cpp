// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "0914Disk.h"
#include "DlgMain.h"
#include "afxdialogex.h"


// CDlgMain 对话框


string CDlgMain::GetFileMD5(const string &file) 
{  
  
    ifstream in(file.c_str(), std::ios::binary);  
    if (!in)  
        return "";  
  
    MD5 md5;  
    std::streamsize length;  
    char buffer[1024];  
    while (!in.eof()) {  
        in.read(buffer, 1024);  
        length = in.gcount();  
        if (length > 0)  
            md5.update(buffer, length);  
    }  
    in.close();  
    return md5.toString();  
}  
  

IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
{

}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_FILE, m_lstFile);
	DDX_Control(pDX, IDC_EDT_CODE, m_edtCode);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_MESSAGE(UM_GETFILELISTMSG,&CDlgMain::GetFileListMsg)
	ON_MESSAGE(UM_INSERTFILEINFOMSG,&CDlgMain::GetFileINfoMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMain::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgMain::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序


BOOL CDlgMain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 0xd)
		return FALSE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_lstFile.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect rect;
	m_lstFile.GetClientRect(&rect);
	int nWidth = rect.Width()/3;

	m_lstFile.InsertColumn(0,"name",0,nWidth,0);
	m_lstFile.InsertColumn(1,"size",0,nWidth,0);
	m_lstFile.InsertColumn(2,"uptime",0,nWidth,0);
	  
	//发送获取文件列表的请求
	STRU_GETFILELIST_RQ sgr;
	sgr.m_userid = m_llUserid;

	if(!theApp.m_pMediator->SendData((char*)&sgr,sizeof(sgr)))
		return FALSE;

    return TRUE;
}
LRESULT CDlgMain::GetFileListMsg(WPARAM wparam,LPARAM lparam)
{
	FileInfo *pFile = (FileInfo*)wparam;
	CString str;
	for(int i = 0;i < lparam;i++)
	{
		m_lstFile.InsertItem(i,pFile[i].m_szFileName);
		str.Format("%lld",pFile[i].m_lFileSize);
		m_lstFile.SetItemText(i,1,str);
		m_lstFile.SetItemText(i,2,pFile[i].m_szFileUpTime);
	}
	return 0;
}

void CDlgMain::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//上传
	CFileDialog dlg(TRUE);
	if(IDOK == dlg.DoModal())
	{
		//获取要上传的文件
		STRU_UPLOADFILE_RQ sur;
		sur.m_nType = _DEF_PROTOCOL_UPLOAD_FILE_RQ;
		sur.m_userid = m_llUserid;
		ZeroMemory(sur.m_szMD5,sizeof(sur.m_szMD5));
		memcpy(sur.m_szFileName,dlg.GetFileName(),sizeof(sur.m_szFileName));
		
		CTime t = CTime::GetCurrentTime();
		CString strTime = t.Format("%Y-%m-%d %H:%M:%S");
		memcpy(sur.m_szFileUpTime,strTime,sizeof(sur.m_szFileUpTime));
		//sur.m_lFileSize = 
		
		{CFile file(dlg.GetPathName(),CFile::modeRead);
		sur.m_lFileSize = file.GetLength();}

		if(sur.m_lFileSize > MAX_STHRESH)
		{
			//sur.m_szMD5=
			string strFile = dlg.GetPathName();
			memcpy(sur.m_szMD5, GetFileMD5(strFile).c_str(),sizeof(sur.m_szMD5));
		}

		FileUpLoadInfo *pInfo = new FileUpLoadInfo;
		pInfo->m_lfileid =0;
		pInfo->m_llfilesize = sur.m_lFileSize;
		pInfo->m_llpos = 0;
		
		memcpy(pInfo->m_szFileName,sur.m_szFileName,sizeof(pInfo->m_szFileName));
		fopen_s(&pInfo->pfile,dlg.GetPathName(),"rb");

		m_mapFileNameToFileInfo[pInfo->m_szFileName]  = pInfo;
		//发送上传文件的请求
		theApp.m_pMediator->SendData((char*)&sur,sizeof(sur));

	}
}
LRESULT CDlgMain::GetFileINfoMsg(WPARAM wparam,LPARAM lparam)
{
	CString str;
	LVFINDINFO info;
    int nIndex;
	int n = m_lstFile.GetItemCount();
	
	FileUpLoadInfo *pInfo = (FileUpLoadInfo *)wparam;

	
	

    info.flags = LVFI_PARTIAL|LVFI_STRING;
	info.psz =pInfo->m_szFileName;

    // Delete all of the items that begin with the string. 
     nIndex = m_lstFile.FindItem(&info);
    if(nIndex == -1)
	{
		m_lstFile.InsertItem(n,pInfo->m_szFileName);
		str.Format("%lld",pInfo->m_llfilesize);
		m_lstFile.SetItemText(n,1,str);
		CTime t = CTime::GetCurrentTime();
		str = t.Format("%Y-%m-%d %H:%M:%S");
		m_lstFile.SetItemText(n,2,str);
	}
	else
	{
		str.Format("%lld",pInfo->m_llfilesize);
		m_lstFile.SetItemText(nIndex,1,str);
		CTime t = CTime::GetCurrentTime();
	    str = t.Format("%Y-%m-%d %H:%M:%S");
		m_lstFile.SetItemText(nIndex,2,str);
	}

	
	return 0;
}

void CDlgMain::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//分享
	//获得要分享的文件

	int nindex = m_lstFile.GetSelectionMark();
	if(-1 == nindex)return ;
	CString strFile = m_lstFile.GetItemText(nindex,0);

	STRU_SHARELINK_RQ ssr;
	ssr.m_nType = _DEF_PROTOCOL_SHARELINK_RQ;
	ssr.m_userid = m_llUserid;
	memcpy(ssr.m_szFileName,strFile,sizeof(ssr.m_szFileName));

	theApp.m_pMediator->SendData((char*)&ssr,sizeof(ssr));
}
