#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <map>
#include "Category.h"
#include "CategoryManager.h"
#include "../include/BaseManager.h"
#include "../database/Constants.h"
#include "Product.h"

using namespace std;

class ProductManager : public BaseManager<Product>
{
public:
    ProductManager(CategoryManager& categoryManager);

    // View 관리
    bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();
    void remove(int id);

private:
    void displayCategories() const;
    void addCategory(Category& category);
    void removeCategory(const std::string& categoryName);

    CategoryManager& mCategoryManager;
};

#endif // PRODUCT_MANAGER_H
