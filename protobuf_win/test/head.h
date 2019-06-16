#pragma once
#include <iostream>
#include <string>
#include "RequestMsg.pb.h"	
using namespace std;
class Codec
{
public:
	Codec();
	virtual string encodeMsg();
	virtual void* decodeMsg();
	virtual ~Codec();
};
struct RequestInfo
{
	int cmd;
	string clientID;
	string serverID;
	string sign;
	string data;
};
class CodecFactory
{
public:
	CodecFactory();
	virtual Codec* createCodec();
	virtual ~CodecFactory();
};

class RequestFactory
{
public:
	RequestFactory(string enc);
	RequestFactory(RequestInfo *info);
	Codec* createCodec();
	~RequestFactory();
private:
	bool m_flage;
	string m_encStr;
	RequestInfo* m_info;
};
class Request :public Codec
{
public:
	Request();
	Request(string encstr);
	Request(struct RequestInfo *info);
	void initMessage(string encstr);
	void initMessage(struct RequestInfo* info);
	string encodeMsg();
	void* decodeMsg();
	~Request();
private:
	string m_encStr;
	RequestMsg m_msg;
};
