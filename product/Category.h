#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <regex>
#include <stdexcept>
#include <vector>

class Product;

using namespace std;

class Category {
public:
    

    Category(const string& category);

    const string& getName() const;

    void addProduct(Product* product);


private:
    string mCategory;
    vector<Product*> mProducts;
};


#endif // CATEGORY_H
