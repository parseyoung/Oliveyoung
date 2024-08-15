#include<iostream>
#include<string>
#include"client.h"
using namespace std;
Client::Client()
{
	mId = 0;
	mName = "";
	mPhoneNum = "";
	mAddress = "";
}
Client::Client(int id, string name, string phoneNum, string address)
{
	mId = id;
	mName = name;
	mPhoneNum = phoneNum;
	mAddress = address;
}
Client::~Client()
{
}
void Client::setName(string name)
{
	mName = name;
}
string Client::getName()
{
	return mName;
}
void Client::setPhoneNum(string phoneNum)
{
	mPhoneNum = phoneNum;
}
string Client::getPhoneNum()
{
	return mPhoneNum;
}
void Client::setAddress(string address)
{
	mAddress = address;
}
string Client::getAddress()
{
	return mAddress;
}
int Client::getId()
{
	return mId;
}
void Client::setId(int id)
{
	mId = id;
}