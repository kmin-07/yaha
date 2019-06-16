#include "TcpServer.h"
#include <errno.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "TcpSocket.h"
TcpServer::TcpServer(){}

TcpServer::~TcpServer(){}

int TcpServer::setListen(unsigned short port)
{
	int ret = 0;
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	m_lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_lfd==-1)
	{
		ret = errno;
		return ret;
	}

	int on = 1;
	ret = setsockopt(m_lfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(servaddr));
	if (ret==-1)
	{
		ret = errno;
		return ret;
	}

	int ret=bind(m_lfd,(struct sockaddr*) &servaddr, sizeof(servaddr));
	if (ret==-1)
	{
		ret = errno;
		return ret;
	}
	ret = listen(m_lfd,128);
	if (ret==-1)
	{
		ret = errno;
		return ret;
	}
	return ret;
}

TcpSocket* TcpServer::acceptConn(int wait_seconds)
{
	int ret;
	if (wait_seconds >0)
	{
		fd_set accpet_fdset;
		struct timeval timeout;
		FD_ZERO(&accpet_fdset);
		FD_SET(m_lfd, &accpet_fdset);

		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;
		do
		{
			ret=select(m_lfd + 1, &accpet_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);
		if (ret<0)
		{
			return NULL;
		}
		struct sockaddr_in addrCli;
		socklen_t addrlen= sizeof(struct sockaddr_in);
		int connfd=accept(m_lfd, (struct sockaddr*) & addrCli, &addrlen);
		if (connfd==-1)
		{
			return NULL;
		}


		return new TcpSocket(connfd);
	}
	return nullptr;
}
