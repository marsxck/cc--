#include "MoveTable.h"



CMoveTable::CMoveTable()
{
	m_nMoveFlag = TABLE_MOVE_LEFT;
}


CMoveTable::~CMoveTable()
{

}
void CMoveTable::GameTableInit(HINSTANCE hIns)
{
	HB_TABLE = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MOVETABLE));

}
void CMoveTable::TableAct(CItem*item)
{
	if (m_nMoveFlag==TABLE_MOVE_LEFT)
	{
		x += 1;
		if (item != NULL)
		{
			item->x = this->x + 15;
		
		}
		if (x > 320)
			m_nMoveFlag = TABLE_MOVE_RIGHT;
	}
	else
	{
		x -= 1;
		if (item != NULL)
		{
			item->x = this->x + 15;
		}
		if (x < 0)
			m_nMoveFlag = TABLE_MOVE_LEFT;
	}
	


}
