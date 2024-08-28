#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

#include "Price.h"
#include "Category.h"

using namespace std;

class Product
{
public:
    Product(unsigned int id, const string& name, const Price& price, const Category& category);
    ~Product();
    bool operator==(const Product& other) const;

    // getter
    const unsigned int getId() const;
    const string& getName() const;
    const Price& getPrice() const;
    const Category& getCategory() const;

    // setter?

    string toString() const;
    static const Product createFromString(const std::string& str);

private:
    unsigned int mId;
    string mName;
    Price mPrice;
    Category mCategory; 
};

#endif // PRODUCT_H