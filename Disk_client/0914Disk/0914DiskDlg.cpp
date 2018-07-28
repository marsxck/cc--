
// 0914DiskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0914Disk.h"
#include "0914DiskDlg.h"
#include "afxdialogex.h"
#include "DlgMain.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy0914DiskDlg 对话框



CMy0914DiskDlg::CMy0914DiskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0914DiskDlg::IDD, pParent)
	, m_edtUserid(15046691258)
	, m_edtPassWord(_T("123456"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0914DiskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_USER, m_edtUserid);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_edtPassWord);
}

BEGIN_MESSAGE_MAP(CMy0914DiskDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy0914DiskDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy0914DiskDlg::OnBnClickedButton2)
	ON_MESSAGE(UM_LOGINMSG,&CMy0914DiskDlg::LoginMsg)
END_MESSAGE_MAP()


// CMy0914DiskDlg 消息处理程序

BOOL CMy0914DiskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy0914DiskDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy0914DiskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy0914DiskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMy0914DiskDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 0xd)
	{
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMy0914DiskDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(); //获得数据
	int n = m_edtPassWord.GetLength();
	if(m_edtUserid < 10000000000 || m_edtUserid >999999999999)
	{
		AfxMessageBox("！！！请重新输入正确的手机号码");
		return;
	}
	if(n <6 || n>20)
	{
		AfxMessageBox("密码长度违规！！！请重新输入密码");
		return;
	}

	//注册
	STRU_REGISTERLOGIN_RQ  srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_lhostip = INet::GetValidIp();
	srr.m_userid = m_edtUserid;
	memcpy(srr.m_szpassword,MD5(m_edtPassWord.GetBuffer()).toString().c_str(),sizeof(srr.m_szpassword));

	theApp.m_pMediator->SendData((char*)&srr,sizeof(srr));

}


void CMy0914DiskDlg::OnBnClickedButton2()
{
	
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(); //获得数据
	int n = m_edtPassWord.GetLength();
	if(m_edtUserid < 10000000000 || m_edtUserid >999999999999)
	{
		AfxMessageBox("！！！请重新输入正确的手机号码");
		return;
	}
	if(n <6 || n>20)
	{
		AfxMessageBox("密码长度违规！！！请重新输入密码");
		return;
	}

	//注册
	STRU_REGISTERLOGIN_RQ  srr;
	srr.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	srr.m_lhostip = INet::GetValidIp();
	srr.m_userid = m_edtUserid;
	memcpy(srr.m_szpassword,MD5(m_edtPassWord.GetBuffer()).toString().c_str(),sizeof(srr.m_szpassword));

	theApp.m_pMediator->SendData((char*)&srr,sizeof(srr));
}
LRESULT CMy0914DiskDlg::LoginMsg(WPARAM wparam,LPARAM lparam)
{
	
	//弹出新窗口
	CDlgMain dlg;
	dlg.m_llUserid = m_edtUserid;
	//关闭登录窗口
	EndDialog(IDOK);
	theApp.m_pMainWnd = &dlg;
	//将窗口指针指向主窗口
	dlg.DoModal();
	return 0;
}