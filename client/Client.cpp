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

// == 연산자 오버로딩: ID가 같으면 두 Client 객체는 동일
bool Client::operator==(const Client& other) const
{
    return (mId == other.mId);
}

// 클라이언트 ID를 반환하는 함수
const unsigned int Client::getId() const
{
    return mId;
}

// 클라이언트 이름을 반환하는 함수
const string Client::getName() const
{
    return mName;
}

// 클라이언트 전화번호를 반환하는 함수
const string Client::getPhoneNumber() const
{
    return mPhoneNumber;
}

// 클라이언트의 포인트를 반환하는 함수
const int Client::getPoint() const
{
    return mPoint;
}

// 클라이언트 정보를 문자열로 변환하는 함수 (ID, 이름, 전화번호, 포인트를 포함)
const string Client::toString() const
{
    return to_string(mId) + "," + mName + "," + mPhoneNumber + "," + to_string(mPoint);
}

// 주어진 문자열을 파싱하여 Client 객체를 생성하는 함수
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

    // Client 객체를 생성하여 반환
    return Client(id, name, phoneNumber, point);
}
