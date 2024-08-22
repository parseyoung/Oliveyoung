#include <iostream>
#include <sstream>

#include "Client.h"

using namespace std;

Client::Client(const unsigned int id, const Name name, const PhoneNumber phoneNumber, const Point point = Point(0))
    : mId(id)
    , mName(name)
    , mPhoneNumber(phoneNumber)
    , mPoint(point)
{
}

Client::~Client()
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

const Name& Client::getName() const
{
    return mName;
}

const PhoneNumber& Client::getPhoneNumber() const
{
    return mPhoneNumber;
}

const Point& Client::getPoint() const
{
    return mPoint;
}

const string Client::toString() const
{
    return to_string(mId) + "," + mName.get() + "," + mPhoneNumber.getFullNumber() + "," + to_string(mPoint.get());
}

const Client Client::createFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int id;
    string nameInput;
    string phoneNumberInput;
    int pointInput;

    // id를 파싱
    if (!(iss >> id >> comma) || comma != ',') {
        throw std::invalid_argument("Invalid client string format (id)");
    }

    // name을 파싱
    if (!std::getline(iss, nameInput, ',')) {
        throw std::invalid_argument("Invalid client string format (name)");
    }

    // phoneNumber를 파싱
    if (!std::getline(iss, phoneNumberInput, ',')) {
        throw std::invalid_argument("Invalid client string format (phoneNumber)");
    }

    // point를 파싱
    if (!(iss >> pointInput)) {
        throw std::invalid_argument("Invalid client string format (point)");
    }

    try {
        Name name(nameInput);
        PhoneNumber phoneNumber(phoneNumberInput);
        Point point(pointInput);

        return Client(id, name, phoneNumber, point);
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid client data: " + std::string(e.what()));
    }
}
