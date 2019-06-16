#define _CRT_SECURE_NO_WARNINGS
#include <openssl/md5.h>
#include <string.h>
#include <cstdio>
#include <iostream>
using namespace std;
void encrypPulickey()
{
	FILE* fd = fopen("public.pem","r");
}
int main()
{
	MD5_CTX c;
	MD5_Init(&c);
	const char* p = "hello world";
	MD5_Update(&c, p, strlen(p));
	unsigned char md[MD5_DIGEST_LENGTH];
	char res[MD5_DIGEST_LENGTH * 2 + 1] = { 0 };
	MD5_Final(md, &c);

	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf(&res[i*2],"%02x",md[i]);
	}
	cout << res << endl;

	return 0;
}

