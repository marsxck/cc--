#include <iostream>

#include "TCPMediator.h"

int main()
{
	IMediator *p = new TCPMediator;
	p->open();

	

	while(1)
	{
		::Sleep(100000);
	}
	system("pause");
	return 0;
}