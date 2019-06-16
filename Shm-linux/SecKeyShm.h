#pragma once
#include "BaseShm.h"
struct NodeShmInfo
{
	int status;
	int seckeyID;
	char clientID[24];
	char serverID[24];
	char seckey[128];
	char pubkey[128];
};
class SecKeyShm:public BaseShm
{
public:
	SecKeyShm(int key);
	SecKeyShm(int key,int maxNode);
	SecKeyShm(const char* name);
	SecKeyShm(const char* name,int maxNode);
	~SecKeyShm();
	int shmWrite(NodeShmInfo* PnodeInfo);
	int shmRead(const char* clientID,const char* serverID, NodeShmInfo* pNodeInfo);
private:
	int m_maxNode;

};