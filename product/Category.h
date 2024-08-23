#ifndef CATEGORY_H
#define CATEGORY_H


#include <string>
#include <map>
#include "Product.h"


using namespace std;


class Category {
public:
    Category(const string& name);
    ~Category();

    void addProduct(Product* product);
    void deleteProduct(int id);
    Product* searchProduct(int id) const;
    void displayProducts() const;

    string getName() const;
    unsigned int getId() const;


private:
    string mName;
    unsigned int mId;
    map<int, Product*> mProductsMap;
};

#endif // CATEGORY_H