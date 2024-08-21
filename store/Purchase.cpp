#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "Purchase.h"

using namespace std;

// Purchase 클래스의 생성자 : 제품 ID와 클라이언트 ID를 받아 Purchase 객체를 생성
Purchase::Purchase(unsigned int productId, unsigned int clientId)
    : mProductId(productId)
    , mClientId(clientId)
    , mDate(chrono::system_clock::now())  // 현재 시간을 구매 날짜로 설정
{
}
// Purchase 클래스의 생성자: 제품 ID, 클라이언트 ID, 특정 시간을 받아 Purchase 객체를 생성
Purchase::Purchase(unsigned int productId, unsigned int clientId, const chrono::system_clock::time_point& date)
    : mProductId(productId)
    , mClientId(clientId)
    , mDate(date) 
{
}
// 제품 ID를 반환하는 getter 메소드
const unsigned int Purchase::getProductId() const
{
    return mProductId;
}
// 클라이언트 ID를 반환하는 getter 메소드
const unsigned int Purchase::getClientId() const
{
    return mClientId;
}

// 구매 날짜를 반환하는 getter 메소드
const chrono::system_clock::time_point Purchase::getDate() const
{
    return mDate;
}

// 시간을 문자열로 변환하는 함수
string Purchase::timePointToString(const chrono::system_clock::time_point& timePoint)
{
    std::time_t t = chrono::system_clock::to_time_t(timePoint);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S"); // "YYYY-MM-DD HH:MM:SS" 형식으로 포맷
    return oss.str();
}

// 문자열을 시간으로 변환하는 함수
chrono::system_clock::time_point Purchase::stringToTimePoint(const string& dateStr) 
{
    std::tm tm = {};
    std::istringstream iss(dateStr);
    iss >> get_time(&tm, "%Y-%m-%d %H:%M:%S"); // 문자열을 파싱하여 std::tm 구조체로 변환
    if (iss.fail()) {
        throw std::invalid_argument("Invalid date format");
    }
    std::time_t t = std::mktime(&tm);
    return chrono::system_clock::from_time_t(t); // std::tm을 시간으로 변환
}

// Purchase 객체를 문자열로 변환하여 반환하는 함수
const string Purchase::toString() const 
{
    return to_string(mProductId) + "," + to_string(mClientId) + "," + timePointToString(mDate);
}

// 주어진 문자열을 이용하여 Purchase 객체를 생성하는 함수
const Purchase Purchase::createPurchaseFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int productId;
    unsigned int clientId;
    string date;

    // 제품 ID를 파싱
    if (!(iss >> productId >> comma) || comma != ',') {
        throw invalid_argument("Invalid format for productId");
    }

    // 클라이언트 ID를 파싱
    if (!(iss >> clientId >> comma) || comma != ',') {
        throw invalid_argument("Invalid format for clientId");
    }

    // 날짜를 파싱
    if (!getline(iss, date)) {
        throw invalid_argument("Invalid format for date");
    }

    return Purchase(productId, clientId, stringToTimePoint(date));
}
