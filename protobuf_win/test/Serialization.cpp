using namespace std;
#include <iostream>
#include "RequestMsg.pb.h"	
#include "head.h"
	Request::Request()
	{
	}
	Request::Request(string encstr)
	{
		this->initMessage(encstr);
	}
	Request::Request(RequestInfo* info)
	{
		this->initMessage(info);
	}
	void Request::initMessage(string encstr)
	{
		this->m_encStr = encstr;
	}
	void Request::initMessage( RequestInfo *info)
	{
		this->m_msg.set_cmdtype (info->cmd);
		this->m_msg.set_clientid (info->clientID);
		this->m_msg.set_serverid (info->serverID);
		this->m_msg.set_sign (info->sign);
		this->m_msg.set_data (info->data);
	}
	string Request::encodeMsg()
	{
		//string str;
		m_msg.SerializeToString(&m_encStr);
		return m_encStr;
	}
	void* Request::decodeMsg()
	{

		m_msg.ParseFromString(m_encStr);
		return (RequestMsg*)&m_msg;
	}
	Request::~Request()
	{

	}
