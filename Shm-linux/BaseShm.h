#pragma once
#pragma once
#include <string>

using namespace std;
class BaseShm
{
public:
	BaseShm() {};
	BaseShm(int key);
	BaseShm(int key, int size);
	BaseShm(string name);
	BaseShm(string name, int size);
	void* mapShm();
	int unmapShm();
	int delShm();
	~BaseShm();
private:
	int getShmID(key_t key, int size, int flag);
	int m_shmid;
	void* m_ptr;

};