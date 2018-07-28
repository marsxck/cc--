#pragma once
#include "afxcmn.h"
#include <map>
#include "afxwin.h"
using namespace std;

// CDlgMain �Ի���
typedef struct FileUpLoadInfo
{
	FILE *pfile;
	long long m_lfileid;
	long long m_llpos;
	long long m_llfilesize;
	char m_szFileName[MAX_PATH];

}FileDownloadInfo;

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMain();

// �Ի�������
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	LRESULT GetFileListMsg(WPARAM wparam,LPARAM lparam);
	LRESULT GetFileINfoMsg(WPARAM wparam,LPARAM lparam);
public:
	static string GetFileMD5(const string &file);
public:
	
	CListCtrl m_lstFile;
	
	long long m_llUserid;
	afx_msg void OnBnClickedButton1();
	map<string,FileUpLoadInfo*> m_mapFileNameToFileInfo;
	//map<long long ,FileUpLoadInfo*> m_mapFileIdToFileInfo;
	CEdit m_edtCode;
	afx_msg void OnBnClickedButton4();
};


