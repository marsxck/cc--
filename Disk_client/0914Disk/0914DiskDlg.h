
// 0914DiskDlg.h : ͷ�ļ�
//

#pragma once


// CMy0914DiskDlg �Ի���
class CMy0914DiskDlg : public CDialogEx
{
// ����
public:
	CMy0914DiskDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0914DISK_DIALOG };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	DECLARE_MESSAGE_MAP()
public:
	
	LONGLONG m_edtUserid;
	CString m_edtPassWord;
public:
	LRESULT LoginMsg(WPARAM wparam,LPARAM lparam);
	
};
