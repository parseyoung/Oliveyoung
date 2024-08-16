#ifndef CATEGORY_H
#define CATEGORY_H

#include "Product.h"
#include <map>
#include <string>


class Category
{
public:

    Category(const string& name); 
    ~Category();

    void addProduct(Product* product);
    void deleteProduct(int id);
    Product* searchProduct(int id) const;
    void displayProducts() const;
    string getName() const;

private:
    string mName;
    map<int, Product*> mProductsMap;

 


};

#endif // CATEGORY_H

