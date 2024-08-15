#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product
{
public:
    Product(unsigned int id, string name, unsigned int price, string category);
    ~Product();
    Product(const Product& other);
    bool operator==(const Product& other) const;

    // getter
    const unsigned int getId() const;
    const string getName() const;
    const unsigned int getPrice() const;
    const string getCategory() const;

    // setter?

    const string toString() const;
    static const Product createFromString(const std::string& str);

private:
    unsigned int mId;
    string mName;
    unsigned int mPrice;
    string mCategory; 
};

#endif // PRODUCT_H