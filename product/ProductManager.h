#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "../include/BaseManager.h"
#include "../database/Constants.h"
#include "Product.h"
#include "../logger/Logger.h"
#include "Category.h"
#include <map>

using namespace std;

class ProductManager : public BaseManager<Product>
{
public:
    ProductManager();

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();
    void displayCategories();
    void displayProductsByCategory(const string& categoryName) const;
    
    const Category* findCategoryByName(const string& categoryName) const;

private:
    static Logger logger;
    map<string, Category> mCategoryMap; 
};

#endif // PRODUCT_MANAGER_H