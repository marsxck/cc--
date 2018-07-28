
// 0914DiskDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0914Disk.h"
#include "0914DiskDlg.h"
#include "afxdialogex.h"
#include "DlgMain.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy0914DiskDlg �Ի���



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


// CMy0914DiskDlg ��Ϣ�������

BOOL CMy0914DiskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy0914DiskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy0914DiskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMy0914DiskDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 0xd)
	{
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMy0914DiskDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(); //�������
	int n = m_edtPassWord.GetLength();
	if(m_edtUserid < 10000000000 || m_edtUserid >999999999999)
	{
		AfxMessageBox("������������������ȷ���ֻ�����");
		return;
	}
	if(n <6 || n>20)
	{
		AfxMessageBox("���볤��Υ�棡������������������");
		return;
	}

	//ע��
	STRU_REGISTERLOGIN_RQ  srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_lhostip = INet::GetValidIp();
	srr.m_userid = m_edtUserid;
	memcpy(srr.m_szpassword,MD5(m_edtPassWord.GetBuffer()).toString().c_str(),sizeof(srr.m_szpassword));

	theApp.m_pMediator->SendData((char*)&srr,sizeof(srr));

}


void CMy0914DiskDlg::OnBnClickedButton2()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(); //�������
	int n = m_edtPassWord.GetLength();
	if(m_edtUserid < 10000000000 || m_edtUserid >999999999999)
	{
		AfxMessageBox("������������������ȷ���ֻ�����");
		return;
	}
	if(n <6 || n>20)
	{
		AfxMessageBox("���볤��Υ�棡������������������");
		return;
	}

	//ע��
	STRU_REGISTERLOGIN_RQ  srr;
	srr.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	srr.m_lhostip = INet::GetValidIp();
	srr.m_userid = m_edtUserid;
	memcpy(srr.m_szpassword,MD5(m_edtPassWord.GetBuffer()).toString().c_str(),sizeof(srr.m_szpassword));

	theApp.m_pMediator->SendData((char*)&srr,sizeof(srr));
}
LRESULT CMy0914DiskDlg::LoginMsg(WPARAM wparam,LPARAM lparam)
{
	
	//�����´���
	CDlgMain dlg;
	dlg.m_llUserid = m_edtUserid;
	//�رյ�¼����
	EndDialog(IDOK);
	theApp.m_pMainWnd = &dlg;
	//������ָ��ָ��������
	dlg.DoModal();
	return 0;
}