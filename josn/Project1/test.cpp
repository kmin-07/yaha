#include <json.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace Json;
void readJson()
{
	ifstream ifs("test.txt");

	Value v;

	Reader rd;
	rd.parse(ifs, v);

	for (int i = 0; i < v.size(); ++i)
	{
		Value sub = v[i];
		if (sub.isInt())
		{
			cout << sub.asInt() << " ";
		}
		else if (sub.isDouble())
		{
			cout << sub.asDouble() << " ";
		}
		else if (sub.isBool())
		{
			cout << sub.asBool() << " ";
		}
		else if (sub.isString())
		{
			cout << sub.isString() << " ";
		}
		else if (sub.isArray())
		{
			for (int j = 0; j <sub.size();++j)
			{
				cout << sub[j].asString() << " ";
			}
		}
		else if (sub.isObject()) 
		{
			cout << sub["name"].asString() << ","
				<< sub["age"].asInt() << " ";
		}
	}


}
int main()
{
	//组织字符串
	Value v;
	v.append(Value(12));
	v.append(19.8);
	v.append(true);
	v.append("hello");
	Value arr;
	arr.append("a");
	arr.append("b");
	arr.append("c");

	v.append(arr);

	Value obj;
	obj["name"] = "xiao";
	obj["age"] = 12;
	v.append(obj);
	
	//格式化字符串
	FastWriter fw;
	string jsonText = fw.write(v);
	string vstyle = v.toStyledString();
	cout << vstyle << endl;
	cout << "josTest:" << jsonText << endl;


	ofstream of;
	of.open("test.txt");
	of << vstyle;
	of.close();

	readJson();

}

