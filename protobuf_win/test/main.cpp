#include "head.h"
using namespace std;
int main()
{
	RequestInfo  info;
	info.cmd = 11;
	info.clientID = "aaa";
	info.serverID = "bbb";
	info.sign = "ccc";
	info.data = "ddd";
	RequestFactory req(&info);
	Codec* codec = req.createCodec();
	string str;
	str = codec->encodeMsg();
	cout << str << "\n" << endl;
	RequestMsg* msg= (RequestMsg * )codec->decodeMsg();
	cout << msg->clientid ()<< "  " << msg->serverid ()<< "  " << endl;

	return 0;
} 