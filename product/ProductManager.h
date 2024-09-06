#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "../include/BaseManager.h"
#include "../include/ViewManager.h"
#include "../database/Constants.h"
#include "Product.h"
#include "../logger/Logger.h"

using namespace std;

class ProductManager : public BaseManager<Product>, public ViewManager
{
public:
    ProductManager();

    // View 관리
    void notify(unsigned int id) override;
    const bool displayMenu() override;
    void displayItemsInfo() const override;
    void inputItem() override;
    void updateProduct(unsigned int id);
    //void notify(unsigned int id);
    void displayProductsByCategory(const string& categoryName);
    void displayCategoryList() const;

    bool isCategoryExists(const string& categoryName) const;
    void addCategory(const string& categoryName);
    Category* getOrCreateCategory(const string& categoryName);

    void CategoryDelete(const string& categoryName);


private:
    static Logger logger;
    map<string, Category*> mCategoryMap; 
};

#endif // PRODUCT_MANAGER_H
