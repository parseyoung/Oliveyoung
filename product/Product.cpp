#include <iostream>
#include <sstream>

#include "Product.h"

using namespace std;

// Product 클래스의 생성자: 제품의 ID, 이름, 가격, 카테고리를 초기화
Product::Product(unsigned int id, string name, unsigned int price, string category)
    : mId(id)
    , mName(name)
    , mPrice(price)
    , mCategory(category)
{
}

// Product 클래스의 소멸자:
Product::~Product()
{
}

// 복사 생성자:
Product::Product(const Product& other)
{
}

// 비교 연산자: 두 Product 객체의 ID가 동일한지 비교
bool Product::operator==(const Product& other) const
{
    return (mId == other.mId);
}

// getter 함수: 각 멤버 변수의 값을 반환
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


// Product 객체를 문자열로 변환 : "ID,이름,가격,카테고리" 형식으로 반환
const string Product::toString() const
{
    return to_string(mId) + "," + mName + "," + to_string(mPrice) + "," + mCategory; 
}

// 주어진 문자열에서 Product 객체를 생성: "ID,이름,가격,카테고리" 형식을 파싱하여 객체 생성
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
