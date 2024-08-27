#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
//#include "Category.h"
#include "Price.h"
class Category;


using namespace std;

class Product
{
public:
    Product(unsigned int id, const string& name, const Price& price, Category* category);
    ~Product();
    Product(const Product& other); 
    Product& operator=(const Product& other); 
    bool operator==(const Product& other) const;

    // getter
    unsigned int getId() const;
    const string& getName() const;
    const Price& getPrice() const;
    const Category& getCategory() const;

    // setter?

    string toString() const;
    static Product createFromString(const string& str);

private:
    unsigned int mId;
    string mName;
    Price mPrice;
    Category* mCategory;
};

#endif // PRODUCT_H