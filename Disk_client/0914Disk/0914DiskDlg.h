
// 0914DiskDlg.h : 头文件
//

#pragma once


// CMy0914DiskDlg 对话框
class CMy0914DiskDlg : public CDialogEx
{
// 构造
public:
	CMy0914DiskDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0914DISK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
