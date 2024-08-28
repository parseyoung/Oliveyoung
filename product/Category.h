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
    explicit Category(const string& name);

    //Category(const string& category) {

    const std::string& getName() const;

    void addProduct(Product* product);

    void removeProduct(Product* product);

    const std::vector<Product*>& getProducts() const;

private:
    string mCategory;
    vector<Product*> mProducts;
};


#endif // CATEGORY_H
