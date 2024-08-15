#include <iostream>
#include <sstream>

#include "Client.h"

using namespace std;

Client::Client(const unsigned int id, const string name, string phoneNumber, int point)
    : mId(id)
    , mName(name)
    , mPhoneNumber(phoneNumber)
    , mPoint(point)
{
}

Client::~Client()
{
}

Client::Client(const Client& other)
{
}

bool Client::operator==(const Client& other) const
{
    return (mId == other.mId);
}

const unsigned int Client::getId() const
{
    return mId;
}

const string Client::getName() const
{
    return mName;
}

const string Client::getPhoneNumber() const
{
    return mPhoneNumber;
}

const int Client::getPoint() const
{
    return mPoint;
}

const string Client::toString() const
{
    return to_string(mId) + "," + mName + "," + mPhoneNumber + "," + to_string(mPoint);
}

const Client Client::createFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int id;
    string name;
    string phoneNumber;
    int point;

      // id를 파싱
    if (!(iss >> id >> comma) || comma != ',') {
        throw std::invalid_argument("Invalid client string format (id)");
    }

    // name을 파싱
    if (!std::getline(iss, name, ',')) {
        throw std::invalid_argument("Invalid client string format (name)");
    }

    // phoneNumber를 파싱
    if (!std::getline(iss, phoneNumber, ',')) {
        throw std::invalid_argument("Invalid client string format (phoneNumber)");
    }

    // point를 파싱
    if (!(iss >> point)) {
        throw std::invalid_argument("Invalid client string format (point)");
    }

    return Client(id, name, phoneNumber, point);
}
