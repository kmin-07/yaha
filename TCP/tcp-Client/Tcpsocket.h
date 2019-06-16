#pragma once
#include <iostream>
using namespace std;
static const int TIMEOUT = 1000;
class TcpSocket
{
public:
	enum ErrorType {ParamError=3003,TimeoutError,PeerCloseError,MallocError};
	TcpSocket();
	TcpSocket(int confd);
	~TcpSocket();
	int connectToHost(string ip, unsigned short port, int timeout);
	int sendMsg(string sendData, int timeout = TIMEOUT);
	string recvMsg(int timrout = TIMEOUT);
	void disConnect();
private:
	int setNonBlock(int fd);

	int setBlock(int fd);
	int readTimeout(unsigned int wait_second);
	int writeTimeout(unsigned int wait_second);
	int connectTimeout(struct sockaddr_in* addr, unsigned int wait_second);
	int readn(void* buf, int count);
	int writren(const void* buf, int count);
private:
	int m_socket;
};