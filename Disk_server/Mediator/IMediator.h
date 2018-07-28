#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#include "Packdef.h"


struct MySocket;
class IMediator
{
public:
	IMediator(){};
	virtual~IMediator(){};
public:
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void DealData(char* szbuf,MySocket *psock) = 0;


};

#endif

