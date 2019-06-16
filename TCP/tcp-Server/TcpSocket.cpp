#include "TcpSocket.h"
#include <arpa\inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

TcpSocket::TcpSocket(){}

TcpSocket::TcpSocket(int connfd)
{
	this->m_socket = connfd;
}

TcpSocket::~TcpSocket(){}

int TcpSocket::connectToHost(string ip, unsigned port, int timeout)
{
	int ret = 0;
	if (port<=0||port>65535||timeout<0)
	{
		ret = ParamError;
		return ret;
	}

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket<0)
	{
		ret = errno;
		printf("func socket() err:  %d\n", ret);
		return ret;
	}


	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(ip.data());

	ret = connectTimeout((struct sockaddr_in*)(&servaddr), (unsigned int)timeout);
	if (ret<0)
	{
		if (ret==-1&&errno==ETIMEDOUT)
		{
			ret = TimeoutError;
			return ret;
		}
		else
		{
			printf("connectTimeout �����쳣, �����: %d\n", errno);
			return errno;
		}
	}
	return ret;
}

int TcpSocket::sendMsg(string sendData, int timeout)
{
	int ret = writeTimeout(timeout);
	if (ret == 0)
	{
		int writed = 0;
		int datalen = sendData.size() + 4;

		unsigned char* netdata = (unsigned char*)malloc(datalen);

		if (netdata==NULL)
		{
			ret - MallocError;
			printf("func sckClient_send() mlloc Err:%d\n ", ret);
			return ret;
		}

		int netlen = htonl(sendData.size());
		memcpy(netdata, &netlen, 4);
		memcpy(netdata + 4, sendData.data(), sendData.size());
		
		writed = writen(netdata, datalen);
		if (writed<datalen)
		{
			if (netdata!=NULL)
			{
				free(netdata);
				netdata = NULL;
			}
			return writed;
		}
		if (netdata != NULL)
		{
			free(netdata);
			netdata = NULL;
		}
		else
		{
			if (ret==-1&&errno==ETIMEDOUT)
			{
				ret = TimeoutError;
				printf("func sckClient_send() mlloc Err:%d\n ", ret);
			}
		}
	}
	return ret;
}

string TcpSocket::recvMsg(int timeout)
{
	int ret = readTimeout(timeout);
		if (ret!=0)
		{
			if (ret==-1||errno==ETIMEDOUT)
			{
				printf("readTimeout err\n");
				return string();
			}
			else
			{
				printf("readTimeout err:%d \n", ret);
				return string();
			}
		}
		int netdatalen = 0;

		ret = readn(&netdatalen, 4);
		if (ret==-1)
		{
			printf("func read() err:%d \n", ret);
			return string();
		}
		else if (ret<4)
		{
			printf("func readn() err peer closed:%d \n", ret);
			return string();
		}
		int n = ntohl(netdatalen);
		char* tmpBuf = (char*)malloc(n + 1);
		if (tmpBuf==NULL)
		{
			ret = MallocError;
			printf("malloc() err \n");
			return NULL;
		}
		ret = readn(tmpBuf, n);
		if (ret==-1)
		{
			printf("func readn() err:%d \n", ret);
			return string();
		}
		if (ret<n)
		{
			printf("func readn() err peer closed:%d \n", ret);
			return string();
		}
		tmpBuf[n] = '\0';
		string data = string(tmpBuf);
		free(tmpBuf);
		return data;
}

void TcpSocket::disConnect()
{
	if (m_socket>=0)
	{
		close(m_socket);
	}
}

int TcpSocket::setNonBlock(int fd)
{
	int flags = fcntl(fd,F_GETFL);
	if (flags==-1)
	{
		return flags;
	}
	flags |= O_NONBLOCK;
	int ret = fcntl(fd, F_SETFL, flags);
	return ret;
}

int TcpSocket::setBlock(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
	{
		return flags;
	}
	flags |= ~O_NONBLOCK;
	int ret = fcntl(fd, F_SETFL, flags);
	return ret;
}

int TcpSocket::readTimeout(unsigned int wait_secondes)
{
	int ret = 0;
	if (wait_secondes>0)
	{
		fd_set read_fdset;
		struct timeval timeout;

		FD_ZERO(&read_fdset);
		FD_SET(m_socket, &read_fdset);

		timeout.tv_sec = wait_secondes;
		timeout.tv_usec = 0;

		do
		{
			select(m_socket + 1, &read_fdset, NULL, NULL, &timeout);
		} while (ret<0&&errno==EINTR);
		if (ret==0)
		{
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret==1)
		{
			ret = 0;
		}
	}
	return ret;
}

int TcpSocket::writeTimeout(unsigned int wait_secondes)
{
	int ret = 0;
	if (wait_secondes > 0)
	{
		fd_set write_fdset;
		struct timeval timeout;

		FD_ZERO(&write_fdset);
		FD_SET(m_socket, &write_fdset);

		timeout.tv_sec = wait_secondes;
		timeout.tv_usec = 0;

		do
		{
			select(m_socket + 1, &write_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);
		if (ret == 0)
		{
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret == 1)
		{
			ret = 0;
		}
	}
	return ret;
}

int TcpSocket::connectTimeout(sockaddr_in* addr, unsigned int wait_secondes)
{
	int ret;
	socklen_t addrlen = sizeof(sizeof(struct sockaddr_in));

	if (wait_secondes>0)
	{
		setNonBlock(m_socket);
	}
	ret = connect(m_socket, (struct sockaddr*)addr, addrlen);
	if (ret<0&&errno==EINPROGRESS)
	{
		fd_set connect_fdset;
		struct timeval timeout;
		FD_ZERO(&connect_fdset);
		FD_SET(m_socket, &connect_fdset);

		do
		{
			select(m_socket + 1, NULL, &connect_fdset, NULL, &timeout);
		} while (ret<0&&errno==EINTR);
		if (ret==0)
		{
			ret == -1;
			errno = ETIMEDOUT;
		}
		else if (ret<0)
		{
			return -1;
		}
		else if (ret==1)
		{
			int err;
			socklen_t socklen = sizeof(err);
			int sockoptret = getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &err, &socklen);
			if (sockoptret==-1)
			{
				return -1;
			}
			if (err==0)
			{
				ret = 0;
			}
			else
			{
				errno = err;
				ret = -1;
			}
		}
	}

	if (wait_secondes>0)
	{
		setBlock(m_socket);
	}
	return ret;
}

int TcpSocket::readn(void* buf, int count)
{
	size_t nleft = count;
	ssize_t nread;
	char* bufp = (char*)buf;
	while (nleft>0)
	{
		if ((nread=read(m_socket,bufp,nleft))<0)
		{
			if (errno==EINTR)
			{
				continue;
			}
			return -1;
		}
		else if (nread = 0)
		{
			return count - nleft;
		}
		bufp += nread;
		nleft -= nread;
	}
	return count;
}

int TcpSocket::writen(const void* buf, int count)
{
	size_t nleft = count;
	ssize_t nwritten;
	char* bufp = (char*)buf;
	while (nleft>0)
	{
		if ((nwritten=write(m_socket,bufp,nleft))<0)
		{
			if (errno==EINTR)
			{
				continue;
			}
			return -1;
		}
		else if (nwritten==0)
		{
			continue;
		}
		bufp += nwritten;
		nleft -= nwritten;
	}
	return count;
}
