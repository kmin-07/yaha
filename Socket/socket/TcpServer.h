#pragma once
#include "TcpSocket.h"
class TcpServer
{public:
	TcpServer();
	int setListen(unsigned short port);
	TcpSocket* acceptConn(int timeout);
	~TcpServer();
private:
	int m_lfd;
};