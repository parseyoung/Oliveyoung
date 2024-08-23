#include <iostream>
#include <sstream>
#include <iomanip>
#include "Product.h"
#include "../store/StockInfo.h"

using namespace std;

Product::Product(unsigned int id, const Category& category, const string& name, const Price& price, const StockInfo& stockInfo)
    : mId(id), mCategory(category), mName(name), mPrice(price), mStockInfo(stockInfo)
{
}

Product::~Product()
{
}

bool Product::operator==(const Product& other) const
{
    return (mId == other.mId);
}

void Product::displayInfo() const {
    std::cout << "ID: " << std::setw(5) << std::setfill('0') << mId << std::endl;
    std::cout << "Name: " << mName << std::endl;
    std::cout << "Price: " << mPrice.get() << std::endl;
    std::cout << "Category: " << mCategory.getName() << std::endl;
    std::cout << "In Stock: " << (mStockInfo.isAvailable() ? "Yes" : "No") << std::endl;
}

// getter
unsigned int Product::getId() const
{
    return mId;
}

const Category& Product::getCategory() const
{
    return mCategory;
}

const string& Product::getName() const
{
    return mName;
}

const Price& Product::getPrice() const
{
    return mPrice;
}

const StockInfo& Product::getStockInfo() const
{
    return mStockInfo;
}

unsigned int Product::getQuantity() const {
    return mStockInfo.getQuantity(); // StockInfo에서 수량 가져오기
}

void Product::setQuantity(unsigned int quantity) {
    mStockInfo.setQuantity(quantity); // StockInfo에서 수량 설정하기
}

void Product::setCategory(const Category& category)
{
    mCategory = category;
}

void Product::setStockInfo(const StockInfo& stockInfo) {
    mStockInfo = stockInfo;
}

string Product::toString() const {
    return to_string(mId) + "," + mCategory.getName() + "," + mName + "," + to_string(mPrice.get()) + "," + to_string(mStockInfo.getQuantity());
}

Product Product::createFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int id;
    string categoryInput;
    string name;
    unsigned int priceInput;
    unsigned int quantity;
    bool availability;

    // id를 파싱
    if (!(iss >> id >> comma) || comma != ',') {
        throw invalid_argument("Invalid product string format (id)");
    }

    // category를 파싱
    if (!getline(iss, categoryInput, ',')) {
        throw invalid_argument("Invalid product string format (category)");
    }

    // name을 파싱
    if (!getline(iss, name, ',')) {
        throw invalid_argument("Invalid product string format (name)");
    }

    // price를 파싱
    if (!(iss >> priceInput >> comma) || comma != ',') {
        throw invalid_argument("Invalid product string format (price)");
    }

    // stockInfo를 파싱
    if (!(iss >> quantity >> comma) || comma != ',' || !(iss >> availability)) {
        throw invalid_argument("Invalid product string format (stock info)");
    }

    try {
        // 파싱된 값을 기반으로 객체 생성
        Price price(priceInput);
        Category category(categoryInput); 
        StockInfo stockInfo(quantity, availability);
        return Product(id, category, name, price, stockInfo);
    } catch (const invalid_argument& e) {
        throw invalid_argument("Invalid product data: " + string(e.what()));
    }
}
