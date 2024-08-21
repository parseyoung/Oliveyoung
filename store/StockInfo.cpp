#include "StockInfo.h"

#include <sstream>

using namespace std;

StockInfo::StockInfo()
{
}
// StockInfo 클래스의 생성자: 수량과 판매가능여부를 받아 객체를 생성
StockInfo::StockInfo(const unsigned int quantity, const bool availability = true)
    : mQuantity(quantity)
    , mAvailability(availability)
{
}

// 재고 수량을 반환하는 getter 메소드
const unsigned int StockInfo::getQuantity() const
{
    return mQuantity;
}

// 판매 가능 여부를 반환하는 getter 메소드
const bool StockInfo::isAvailable() const
{
    return mAvailability;
}

// 재고 수량을 설정하는 setter 메소드
void StockInfo::setQuantity(const unsigned int quantity)
{
    mQuantity = quantity;
}

// 판매 가능 여부를 설정하는  setter 메소드
void StockInfo::setAvailability(const bool availability)
{
    mAvailability = availability;
}

// 주어진 문자열을 이용하여 StockInfo 객체를 생성하는 함수
const StockInfo StockInfo::createFromString(const std::string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int quantity;
    bool availability;

    // 수량을 파싱
    if (!(iss >> quantity >> comma) || comma != ',') {
        throw invalid_argument("Invalid stock info format (quantity)");
    }

    // 가용성 여부 파싱
    if (!(iss >> availability)) {
        throw invalid_argument("Invalid stock info format (availability)");
    }

    return StockInfo(quantity, availability); // 파싱된 정보로 StockInfo 객체 생성
}
}

// StockInfo 객체를 문자열로 변환하여 반환하는 함수
const string StockInfo::toString() const
{
    return to_string(mQuantity) + "," + to_string(mAvailability);
}
