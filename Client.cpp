#include "Client.h"


Client::Client(int mId, string mName, string mPhone, int mPoints)
    : mId(mId), mName(mName), mPhone(mPhone), mPoints(mPoints) {}

Client::~Client() {}

void Client::displayInfo() const
{
    cout << "ID : " << mId << ", Name : " << mName << ", Phone : " << mPhone << ", Points : " << mPoints;
}

int Client::getId() const 
{
    return mId;
}

string Client::getName() const 
{
    return mName;
}

string Client::getPhone() const 
{
    return mPhone;
}

int Client::getPoints() const 
{
    return mPoints;
}
