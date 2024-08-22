#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "../include/BaseManager.h"
#include "../database/Constants.h"
#include "Product.h"

using namespace std;

class ProductManager : public BaseManager<Product>
{
public:
    ProductManager();

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();

private:
};

#endif // PRODUCT_MANAGER_H