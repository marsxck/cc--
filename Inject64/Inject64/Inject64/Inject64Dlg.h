
// Inject64Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CInject64Dlg �Ի���
class CInject64Dlg : public CDialogEx
{
// ����
public:
	CInject64Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_INJECT64_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox mProcList;
	CMFCEditBrowseCtrl mDllEditBrowse;
	afx_msg void OnBnClickedOk2();
};
