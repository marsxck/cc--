#include "OnceTable.h"



COnceTable::COnceTable()
{
}


COnceTable::~COnceTable()
{
}
void COnceTable::GameTableInit(HINSTANCE hIns)
{
	HB_TABLE = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_ONCETABLE));
}
