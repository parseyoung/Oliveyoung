#pragma once
#include <string>
#include <iostream>
using namespace std;

class Client
{
private:
	int mId;
	string mName;
	string mPhone;
	int mPoints;

public:
	Client(int mId = 0, string mName = "", string mPhone = "", int mPoints = 0);
	~Client();
	int getId() const ;
	string getName() const;
	string getPhone() const;
	int getPoints() const;
	void displayInfo() const;

};

