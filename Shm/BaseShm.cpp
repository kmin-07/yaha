#include "BaseShm.h"


BaseShm::BaseShm(int key)
{
	getShmID(key, 0, 0);
}

BaseShm::BaseShm(int key, int size)
{
	getShmID(key, size, IPC_CREAT|0664);
}

BaseShm::BaseShm(string name)
{
	key_t key = ftok(name.data(), 'x');
	getShmID(key, 0, 0);
}

BaseShm::BaseShm(string name, int size)
{
	key_t key = ftok(name.data(), 'x');
	getShmID(key, size, 0);
}

void* BaseShm::mapShm()
{
	m_ptr = shmat(m_shmid, NULL, 0);
	return m_ptr;
}

int BaseShm::unmapShm()
{
	int ret=
	return 0;
}

int BaseShm::delShm()
{
	return 0;
}

int BaseShm::getShmID(int key, int size, int flag)
{
	return 0;
}
