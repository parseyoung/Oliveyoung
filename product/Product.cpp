#include <iostream>
#include <sstream>

#include "Product.h"

using namespace std;

Product::Product(unsigned int id, string name, unsigned int price, string category)
    : mId(id)
    , mName(name)
    , mPrice(price)
    , mCategory(category)
{
}

Product::~Product()
{
}

Product::Product(const Product& other)
{
}

bool Product::operator==(const Product& other) const
{
    return (mId == other.mId);
}

// getter
const unsigned int Product::getId() const
{
    return mId;
}

const string Product::getName() const
{
    return mName;
}

const unsigned int Product::getPrice() const
{
    return mPrice;
}

const string Product::getCategory() const
{
    return mCategory;
}

// setter?

const string Product::toString() const
{
    return to_string(mId) + "," + mName + "," + to_string(mPrice) + "," + mCategory; 
}

const Product Product::createFromString(const std::string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int id;
    string name;
    int price;
    string category;


    // id를 파싱
    if (!(iss >> id >> comma) || comma != ',') {
        throw invalid_argument("Invalid product string format (id)");
    }

    // name을 파싱
    if (!std::getline(iss, name, ',')) {
        throw invalid_argument("Invalid product string format (name)");
    }

    // price를 파싱
    if (!(iss >> price >> comma) || comma != ',') {
        throw invalid_argument("Invalid product string format (price)");
    }

    // category를 파싱
    if (!std::getline(iss, category)) {
        throw invalid_argument("Invalid product string format (category)");
    }

    return Product(id, name, price, category);
}
