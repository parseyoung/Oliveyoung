#ifndef STORE_H
#define STORE_H

#include <string>
#include <map>
#include <utility>

#include "StockInfo.h"

using namespace std;

class Store
{
    friend class StoreManager;

public:
    Store(string storeName);
    ~Store();
    Store(const Store& other);

    const string getName() const;

    static const pair<unsigned int, StockInfo> createStockInfoFromString(const string& str); 
    static const string toStockInfoString(const unsigned int productId, const StockInfo& stockInfo); 

private:
    map<unsigned int, StockInfo>& getProductStockMap();
    void initialize(const map<unsigned int, StockInfo> productStockMap);

    string mName;
    map<unsigned int, StockInfo> mProductStockMap;
};

#endif // STORE_H
