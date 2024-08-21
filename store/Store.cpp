#include <iostream>
#include <sstream>

#include "Store.h"
#include "StockInfo.h"

// Store 클래스의 생성자: 상점 이름을 받아 객체를 생성
Store::Store(string storeName) 
    : mName(storeName) {}

Store::~Store() {}

// Store 클래스의 복사 생성자
Store::Store(const Store& other)
    : mName(other.mName), mProductStockMap(other.mProductStockMap) {}

// 상점 이름을 반환하는 getter 메소드
const string Store::getName() const 
{
    return mName;
}

// 제품 재고 맵을 반환하는 getter 메소드
map<unsigned int, StockInfo>& Store::getProductStockMap()
{
    return mProductStockMap;
}
// 제품 재고 맵을 초기화하는 함수
void Store::initialize(const map<unsigned int, StockInfo> productStockMap)
{
    mProductStockMap = productStockMap;
}
// 주어진 문자열을 이용하여 제품 ID와 StockInfo 객체를 생성하는 함수
const pair<unsigned int, StockInfo> Store::createStockInfoFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int productId;

    // 첫 번째 콤마 이전의 상품 ID 부분만 파싱
    if (!(iss >> productId >> comma) || comma != ',') {
        throw invalid_argument("Invalid stock info data");
    }

    // 나머지 부분은 StockInfo 생성에 사용
    string remainingStr;
    if (!getline(iss, remainingStr)) {
        throw invalid_argument("Invalid stock info data");
    }

    StockInfo stockInfo = StockInfo::createFromString(remainingStr);

    return { productId, stockInfo };
}
// 제품 ID와 StockInfo 객체를 문자열로 변환하는 함수
const string Store::toStockInfoString(const unsigned int productId, const StockInfo& stockInfo) 
{
    return to_string(productId) + "," + stockInfo.toString();
}
