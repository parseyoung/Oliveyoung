#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "Price.h"
#include "Category.h"
#include "../store/StockInfo.h"

using namespace std;

class Product
{
public:
    Product(unsigned int id, const Category& category, const string& name, const Price& price, const StockInfo& stockInfo);
    ~Product();

    bool operator==(const Product& other) const;
    void displayInfo() const;

    // getter methods
    unsigned int getId() const;
    const Category& getCategory() const;
    const string& getName() const;
    const Price& getPrice() const;
    const StockInfo& getStockInfo() const;
    unsigned int getQuantity() const;

    // setter methods
    void setQuantity(unsigned int quantity);
    void setCategory(const Category& category);
    void setStockInfo(const StockInfo& stockInfo);

    string toString() const;
    static Product createFromString(const string& str);

private:
    unsigned int mId;
    Category mCategory;
    string mName;
    Price mPrice;
    StockInfo mStockInfo;
};

#endif // PRODUCT_H
