
// Inject64Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Inject64.h"
#include "Inject64Dlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include <AtlConv.h>

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


// CInject64Dlg �Ի���



CInject64Dlg::CInject64Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInject64Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInject64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mProcList);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, mDllEditBrowse);
}

BEGIN_MESSAGE_MAP(CInject64Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CInject64Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CInject64Dlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CInject64Dlg ��Ϣ�������

BOOL CInject64Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	mDllEditBrowse.EnableFileBrowseButton(NULL, _T("Dll Files (*.dll)|*.dll|All Files (*.*)|*.*||"));
	CInject64Dlg::OnBnClickedOk();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CInject64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInject64Dlg::OnPaint()
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
HCURSOR CInject64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//Զ�̼���dll
BOOL RemoteLoadLibrary(HANDLE hProcess, LPCSTR lpLibFileName)
{
	//����ռ�
	PCHAR lpRemoteLibFileName = (PCHAR)VirtualAllocEx(hProcess, NULL, lstrlenA(lpLibFileName) + 1, MEM_COMMIT, PAGE_READWRITE);
	if (lpRemoteLibFileName == NULL)
	{
		return FALSE;
	}
	WriteProcessMemory(hProcess, lpRemoteLibFileName, (void *)lpLibFileName, lstrlenA(lpLibFileName) + 1, NULL);
	//PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("Kernel32")), "LoadLibraryA");
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)LoadLibraryA;
	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnStartAddr, lpRemoteLibFileName, 0, NULL);
	if (hRemoteThread == NULL)
	{
		return FALSE;
	}
	WaitForSingleObject(hRemoteThread, INFINITE);
	DWORD ExitCode;
	GetExitCodeThread(hRemoteThread, &ExitCode);
	CloseHandle(hRemoteThread);
	VirtualFreeEx(hProcess, lpRemoteLibFileName, 0, MEM_RELEASE);

	return ExitCode;
}

void CInject64Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);

	mProcList.ResetContent();

	DWORD dwPid = 0;
	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return ;

	Process32First(hProcessSnap, &pe32);
	do
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
		BOOL isWow64;
		if (IsWow64Process(hProcess, &isWow64))
		{
			TCHAR szBuf[1024] = { 0 };
			if (isWow64 || sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
			{
				wsprintf(szBuf, _T("%s %4d %s"), _T("(32λ)"), pe32.th32ProcessID, pe32.szExeFile);
			}
			else
			{
				wsprintf(szBuf, _T("%s %4d %s"), _T("(64λ)"), pe32.th32ProcessID, pe32.szExeFile);
			}
			int count = mProcList.AddString(szBuf);
			mProcList.SetItemData(count, pe32.th32ProcessID);
		}
		CloseHandle(hProcess);
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	//CDialogEx::OnOK();
}


void CInject64Dlg::OnBnClickedOk2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	USES_CONVERSION;

	//��ȡѡ���dll·��
	CString dllPath;
	mDllEditBrowse.GetWindowText(dllPath);

	//��ȡѡ�еĽ���id,���򿪽���
	DWORD pid = mProcList.GetItemData(mProcList.GetCurSel());
	HANDLE hProcess = OpenProcess(\
		PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | SYNCHRONIZE | PROCESS_VM_WRITE | PROCESS_VM_READ, \
		FALSE, pid);
	if (INVALID_HANDLE_VALUE == hProcess || NULL == hProcess)
	{
		AfxMessageBox(_T("�򿪽���ʧ��!"));
		return;
	}

	if (RemoteLoadLibrary(hProcess, W2A(dllPath)))
	{
		AfxMessageBox(_T("ע��ɹ�!"));
	}
	else
	{
		AfxMessageBox(_T("ע��ʧ�ܣ�����Ƿ�ѡ����Ҫע����̺�DLL!"));
	}
}
