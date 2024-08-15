#include <iostream>
#include <sstream>

#include "Store.h"
#include "StockInfo.h"

Store::Store(string storeName) 
    : mName(storeName)
{
}

Store::~Store() 
{
}

Store::Store(const Store& other)
    : mName(other.mName)
    , mProductStockMap(other.mProductStockMap)
{
}

const string Store::getName() const 
{
    return mName;
}


map<unsigned int, StockInfo>& Store::getProductStockMap()
{
    return mProductStockMap;
}

void Store::initialize(const map<unsigned int, StockInfo> productStockMap)
{
    mProductStockMap = productStockMap;
}

const pair<unsigned int, StockInfo> Store::createStockInfoFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int productId;

    // 첫 번째 콤마 이전의 productId 부분만 파싱
    if (!(iss >> productId >> comma) || comma != ',') {
        throw invalid_argument("Invalid stock info data");
    }

    // 나머지 부분은 그대로 넘김
    string remainingStr;
    if (!getline(iss, remainingStr)) {
        throw invalid_argument("Invalid stock info data");
    }

    StockInfo stockInfo = StockInfo::createFromString(remainingStr);

    return { productId, stockInfo };
}

const string Store::toStockInfoString(const unsigned int productId, const StockInfo& stockInfo) 
{
    return to_string(productId) + "," + stockInfo.toString();
}
