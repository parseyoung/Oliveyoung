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
    const bool displayMenu() override;
    void displayItemsInfo() const override;
    void inputItem() override;

    void notify(unsigned int id);
    void displayProductsByCategory(const string& categoryName);
    void displayCategoryList() const;

private:
    static Logger logger;
};

#endif // PRODUCT_MANAGER_H
