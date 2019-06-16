#include "BaseShm.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <iostream>
BaseShm::BaseShm(int key)
{
	getShmID(key, 0, 0);
}

BaseShm::BaseShm(int key, int size)
{
	getShmID(key, size, IPC_CREAT | 0664);
}

BaseShm::BaseShm(string name)
{
	key_t key = ftok(name.data(), 'x');
	getShmID(key, 0, 0);
}

BaseShm::BaseShm(string name, int size)
{
	key_t key = ftok(name.data(), 'x');
	getShmID(key, size, IPC_CREAT|0664);
}

void* BaseShm::mapShm()
{
	m_ptr = shmat(m_shmid,NULL, 0);
	if (m_ptr==(void*)-1)
	{
		return NULL;
	}
	return m_ptr;
}

int BaseShm::unmapShm()
{
	int ret = shmdt(m_ptr);
		return ret;
}

int BaseShm::delShm()
{
	int ret = shmctl(m_shmid, IPC_RMID, NULL);
	return ret;
}

BaseShm::~BaseShm()
{
}



int BaseShm::getShmID(key_t key, int size, int flag)
{
	m_shmid = shmget(key, size, flag);
	if (m_shmid==-1)
	{
		cout << "fail" << endl;
	}
	if (m_shmid>0)
	{
		void* addr = shmat(m_shmid, NULL, 0);
		memset(addr, 0, size);
	}
	return m_shmid;
}