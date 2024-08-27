#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
//#include "Product.h"
class Product;
using namespace std;



class Category {
public:
    Category() = default;
    Category(const string& name);

    // 복사 생성자 및 대입 연산자
    Category(const Category& other);
    Category& operator=(const Category& other);


    void addProduct(Product* product);
    const vector<Product*>& getProducts() const;
    const string& getName() const;

    

private:
    string mName;
    vector<Product*> mProduct;
};

#endif // CATEGORY_H
