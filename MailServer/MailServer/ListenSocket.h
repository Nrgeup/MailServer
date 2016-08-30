#pragma once
#include "MySocket.h"
// ListenSocket 命令目标

class ListenSocket : public CAsyncSocket
{
public:
	ListenSocket();
	virtual ~ListenSocket();

	MySocket *m_pSocket; //指向一个连接的socket对象
	virtual void OnAccept(int nErrorCode);
};


