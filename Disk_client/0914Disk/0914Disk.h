
// 0914Disk.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TCPMediator.h"
#include "Packdef.h"
#include "md5.h"
// CMy0914DiskApp:
// �йش����ʵ�֣������ 0914Disk.cpp
//

class CMy0914DiskApp : public CWinApp
{
public:
	CMy0914DiskApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	IMediator *m_pMediator;
	virtual int ExitInstance();
};

extern CMy0914DiskApp theApp;