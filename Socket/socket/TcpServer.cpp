#include "TcpServer.h"
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include 
TcpServer::TcpServer()
{

}

int TcpServer::setListen(unsigned short port)
{
	return 0;
}

TcpSocket* TcpServer::acceptConn(int timeout)
{
	return nullptr;
}

TcpServer::~TcpServer()
{
}
