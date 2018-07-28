
// 0914Disk.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TCPMediator.h"
#include "Packdef.h"
#include "md5.h"
// CMy0914DiskApp:
// 有关此类的实现，请参阅 0914Disk.cpp
//

class CMy0914DiskApp : public CWinApp
{
public:
	CMy0914DiskApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
public:
	IMediator *m_pMediator;
	virtual int ExitInstance();
};

extern CMy0914DiskApp theApp;