#include<windows.h>
#include<tchar.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		MessageBox(NULL, _T("DLL�ѽ���Ŀ����̡�"), _T("��Ϣ"), MB_ICONINFORMATION);
	}
	break;
	case DLL_PROCESS_DETACH:
	{
		MessageBox(NULL, _T("DLL�Ѵ�Ŀ�����ж�ء�"), _T("��Ϣ"), MB_ICONINFORMATION);
	}
	break;
	}
	return TRUE;
}