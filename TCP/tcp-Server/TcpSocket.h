#pragma once
#include <iostream>
using namespace std;
static const int TIMEOUT = 10000;
class TcpSocket
{
public:
	enum ErrorType {ParamError=3001,TimeoutError,PeerCloseError,MallocError};
	TcpSocket();
	TcpSocket(int connfd);
	~TcpSocket();

	int connectToHost(string ip, unsigned port, int timeout = TIMEOUT);

	int sendMsg(string sendData, int timeout = TIMEOUT);

	string recvMsg(int timeout = TIMEOUT);

	void disConnect();

private:
	int setNonBlock(int fd);

	int  setBlock(int fd);

	int readTimeout(unsigned int wait_secondes);

	int writeTimeout(unsigned int wait_secondes);

	int connectTimeout(struct sockaddr_in* addr, unsigned int wait_secondes);

	int readn(void* buf, int count);

	int writen(const void* buf, int count);

private:
	int m_socket;
};