#pragma once
#include "afxcmn.h"
#include <map>
#include "afxwin.h"
using namespace std;

// CDlgMain 对话框
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
	CDlgMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMain();

// 对话框数据
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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


