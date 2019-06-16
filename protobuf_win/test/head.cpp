#include "head.h"
Codec::Codec(){}
string Codec::encodeMsg()
{
	return string();
}

void* Codec::decodeMsg()
{
	return nullptr;
}

Codec::~Codec(){}

CodecFactory::CodecFactory(){}

Codec* CodecFactory::createCodec()
{
	return nullptr;
}

CodecFactory::~CodecFactory(){}

RequestFactory::RequestFactory(string enc)
{
	this->m_flage = true;
	this->m_encStr = enc;
}

RequestFactory::RequestFactory(RequestInfo *info)
{
	this->m_flage = false;
	this->m_info = info;
}

Codec* RequestFactory::createCodec()
{
	Codec* codec = NULL;
	if (m_flage==true)
	{
		codec = new Request(m_encStr);
	}
	else
	{
		codec = new Request(m_info);
	}
	return codec;
}

RequestFactory::~RequestFactory()
{

}
