#ifndef __CLIENT_H_
#define __CLIENT_H_
#include <string>
using namespace std;
class Client
{
public:
	Client(int id, string name, string phoneNum, string address);
	Client();
	~Client();
	void setName(string name);
	string getName();
	void setPhoneNum(string phoneNum);
	string getPhoneNum();
	void setAddress(string address);
	string getAddress();
	int getId();
	void setId(int id);
private:
	int mId;
	string mName;
	string mPhoneNum;
	string mAddress;


};

#endif