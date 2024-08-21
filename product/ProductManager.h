#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "../include/BaseManager.h"
#include "../database/Constants.h"
#include "Product.h"

using namespace std;

// 저장소
namespace ProductManagerConstants {
    const string RESOURCE = DIR_DATABASE + "product_list.csv";
}

class ProductManager : public BaseManager<Product>
{
public:
    ProductManager() : BaseManager<Product>(ProductManagerConstants::RESOURCE) {};

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();

private:
};

#endif // PRODUCT_MANAGER_H