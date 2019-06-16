#include "SecKeyShm.h"
#include "BaseShm.h"
#include <string.h>
#include <errno.h>
SecKeyShm::SecKeyShm(int key)
{
	BaseShm(key);
}

SecKeyShm::SecKeyShm(int key, int maxNode)
{
	BaseShm(key, sizeof(NodeShmInfo) * maxNode);
	m_maxNode = maxNode;
}

SecKeyShm::SecKeyShm(const char* name)
{
	BaseShm(name);
}

SecKeyShm::SecKeyShm(const char* name, int maxNode)
{
	BaseShm(name, sizeof(NodeShmInfo) * maxNode);
	m_maxNode = maxNode;
}

SecKeyShm::~SecKeyShm()
{
}

int SecKeyShm::shmWrite(NodeShmInfo* PnodeInfo)
{
	NodeShmInfo* paddr = (NodeShmInfo*)mapShm();
	int ret = -1;
	NodeShmInfo* pnode = NULL;
	if (paddr==NULL)
	{
		return -1;
	}
	for (int i = 0; i <m_maxNode;++i)
	{
		pnode = paddr + i;
		if (strcmp(pnode->clientID,PnodeInfo->clientID)==0&&strcmp(pnode->serverID,PnodeInfo->serverID)==0)
		{
			memcpy(pnode, PnodeInfo, sizeof(NodeShmInfo));
			unmapShm();
			return 0;
		}
	}
	int i = 0;
	for ( i = 0; i < m_maxNode; ++i)
	{
		pnode = paddr + i;
		if (memcmp(0,pnode,sizeof(NodeShmInfo)==0))
		{
			memcpy(pnode, PnodeInfo, sizeof(NodeShmInfo));
			break;
		}
	}
	if (i=m_maxNode)
	{
		return -1;
	}
	unmapShm();
	return 0;
}

int SecKeyShm::shmRead(const char* clientID, const char* serverID, NodeShmInfo* pNodeInfo)
{
	NodeShmInfo* paddr = (NodeShmInfo*)mapShm();
	int ret = -1;
	NodeShmInfo* pnode = NULL;
	if (paddr == NULL)
	{
		return -1;
	}
	int i = 0;
	for ( i = 0; i < m_maxNode; ++i)
	{
		pnode = paddr + i;
		if (strcmp(pnode->clientID,clientID) == 0 && strcmp(pnode->serverID,serverID) == 0)
		{
			memcpy(pNodeInfo, pnode, sizeof(NodeShmInfo));
			break;
		}
	}
	if (i==m_maxNode)
	{
		return -1;
	}
	unmapShm();
	return 0;
}
