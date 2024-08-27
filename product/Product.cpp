#include <iostream>
#include <sstream>
#include "Category.h"
#include "Product.h"

using namespace std;

Product::Product(unsigned int id, const string& name, const Price& price, Category* category)
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
    : mId(other.mId), mName(other.mName), mPrice(other.mPrice), mCategory(other.mCategory)
{
}

Product& Product::operator=(const Product& other)
{
    if (this != &other) {
        mId = other.mId;
        mName = other.mName;
        mPrice = other.mPrice;
        mCategory = other.mCategory;
    }
    return *this;
}

bool Product::operator==(const Product& other) const
{
    return (mId == other.mId);
}

// getter
unsigned int Product::getId() const
{
    return mId;
}

const string& Product::getName() const
{
    return mName;
}

const Price& Product::getPrice() const
{
    return mPrice;
}

const Category& Product::getCategory() const
{
    return *mCategory;
}

// setter?

string Product::toString() const
{
    return to_string(mId) + "," + mName + "," + to_string(mPrice.get()) + "," + mCategory->getName();
}

Product Product::createFromString(const std::string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int id;
    string name;
    unsigned int priceInput;
    string categoryInput;

    // id를 파싱
    if (!(iss >> id >> comma) || comma != ',') {
        throw invalid_argument("Invalid product string format (id)");
    }

    // name을 파싱
    if (!std::getline(iss, name, ',')) {
        throw invalid_argument("Invalid product string format (name)");
    }

    // price를 파싱
    if (!(iss >> priceInput >> comma) || comma != ',') {
        throw invalid_argument("Invalid product string format (price)");
    }

    // category를 파싱
    if (!std::getline(iss, categoryInput)) {
        throw invalid_argument("Invalid product string format (category)");
    }

    try {
        // 파싱된 값을 기반으로 객체 생성
        Price price(priceInput);
        Category* category = new Category(categoryInput);

        return Product(id, name, price, category);
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid product data: " + std::string(e.what()));
    }
}