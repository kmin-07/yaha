#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <string>
using namespace std;
class TcpSocket
{
public:
	TcpSocket();
	TcpSocket(int connfd);
	int connectToHost(string ip, unsigned short port, int timeout);
private:
	int m_socket;
};