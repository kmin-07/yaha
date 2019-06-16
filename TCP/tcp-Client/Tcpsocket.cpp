#include "Tcpsocket.h"

TcpSocket::TcpSocket()
{
}

TcpSocket::TcpSocket(int confd)
{
}

TcpSocket::~TcpSocket()
{
}

int TcpSocket::connectToHost(string ip, unsigned short port, int timeout)
{
	return 0;
}

int TcpSocket::sendMsg(string sendData, int timeout)
{
	return 0;
}

string TcpSocket::recvMsg(int timrout)
{
	return string();
}

void TcpSocket::disConnect()
{
}

int TcpSocket::setNonBlock(int fd)
{
	return 0;
}

int TcpSocket::setBlock(int fd)
{
	return 0;
}

int TcpSocket::readTimeout(unsigned int wait_second)
{
	return 0;
}

int TcpSocket::writeTimeout(unsigned int wait_second)
{
	return 0;
}

int TcpSocket::connectTimeout(sockaddr_in* addr, unsigned int wait_second)
{
	return 0;
}

int TcpSocket::readn(void* buf, int count)
{
	return 0;
}

int TcpSocket::writren(const void* buf, int count)
{
	return 0;
}
