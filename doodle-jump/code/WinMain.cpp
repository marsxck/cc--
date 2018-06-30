#include <windows.h>
#include "CGameCtrl.h"
//#include<gdiplus.h>
#include"JumpApp.h"
#include <time.h>
//using namespace Gdiplus;
//#pragma comment (lib,"gdiplus.lib")
HINSTANCE hIns;

PFUN_CREATE_OBJECT CGameCtrl::pfnCreateObject = 0;

CGameCtrl* pCtrl = NULL;

//  ������Ϣ ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_CREATE:  // ��ʼ������
		if(CGameCtrl::pfnCreateObject == NULL)
		{
			::MessageBox(NULL,"��Ϸ����ʧ��","��ʾ",MB_OK);
			::DestroyWindow(hWnd);  //  ���ٴ���;
			::PostQuitMessage(0);  //  �˳�
			return 0;
		}
		else
		{ 
			//  ���ú���ָ��  ��������Ķ���
			pCtrl = (*CGameCtrl::pfnCreateObject)();
			//  ���þ��
			pCtrl->SetHandle(hWnd,hIns);
			//  ��ʼ����Ϸ
			pCtrl->OnCreateGame();
		}
		break;
	case WM_PAINT:
		if(pCtrl != NULL)
		{
			pCtrl->OnGameDraw();
		}
		break;
	case WM_TIMER:
		if(pCtrl != NULL)
		{
			pCtrl->OnGameRun(wParam);
		}
		break;
	case WM_KEYDOWN:
		if(pCtrl != NULL)
		{
			pCtrl->OnKeyDown(wParam);
		}
		break;
	case WM_KEYUP:
		if(pCtrl != NULL)
		{
			pCtrl->OnKeyUp(wParam);
		}
		break;
	case WM_LBUTTONDOWN:
		Point.x = LOWORD(lParam);
		Point.y = HIWORD(lParam);
		if(pCtrl != NULL)
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			pCtrl->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		if(pCtrl != NULL)
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			pCtrl->OnLButtonUp(point);
		}
		break;
	case MM_MCINOTIFY:
		mciSendCommand(CJumpApp::m_mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)(LPVOID)&CJumpApp::m_mciPlay);
		break;
	case WM_MOUSEMOVE:
		if(pCtrl != NULL)
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			pCtrl->OnMouseMove(point);
		}
		break;
	case WM_CLOSE:   //  ��X  ���ڹرյ���Ϣ
		delete pCtrl;  //  ɾ����Ϸ
		pCtrl = NULL;
		::PostQuitMessage(0);    //  �����˳�����Ϣ
		break;
	}
	return ::DefWindowProc( hWnd,  uMsg,  wParam,  lParam);
}















































int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance, LPSTR pCmdLine,int nCmdShow)
{
	srand((unsigned int)time(0));

	hIns = hInstance;
	HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
	//ULONG_PTR token;
	//::GdiplusStartupInput gdi;
	//GdiplusStartup(&token,&gdi,NULL);//��ʼGDI+
	//  1.  ���
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;   //  �Ƿ�Ҫ�������Ŀռ�
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hbrBackground = hBrush;   //  ������ɫ
	wndclass.hCursor = NULL; //  ���
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;  //  ��������Сͼ��
	wndclass.hInstance = hInstance;    //  ��ǰʵ���ľ��
	wndclass.lpfnWndProc = WndProc;    //  ��Ϣ������
	wndclass.lpszClassName = "lele";   //  ע�ᴰ�������
	wndclass.lpszMenuName = NULL;       //  �˵���
	wndclass.style = CS_HREDRAW|CS_VREDRAW;   //  ���������ʽ


	//  2.  ע��
	if(::RegisterClassEx(&wndclass) == FALSE)
	{
		::MessageBox(NULL,"ע��ʧ��","��ʾ",MB_OK);
		return 0;
	}


	//  3.  ����
	HWND hWnd = ::CreateWindow("lele","~O(��_��)O~",WS_OVERLAPPEDWINDOW,550,180,380+16,550+38,NULL,NULL,hInstance,NULL);
	if(hWnd == NULL)
	{
		::MessageBox(NULL,"����ʧ��","��ʾ",MB_OK);
		return 0;
	}
	
	

	//  4.   ��ʾ
	::ShowWindow(hWnd,SW_SHOW); 

	//  5.   ��Ϣѭ��
	MSG msg;
	while(::GetMessage(&msg,0,0,0))
	{
		//  ����
		::TranslateMessage(&msg);
		//  �ַ�
		::DispatchMessage(&msg);
	}

	//  ɾ����ˢ
	//::GdiplusShutdown(token);
	::DeleteObject(hBrush);
	return 0;
}