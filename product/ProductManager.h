#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "../database/Constants.h"
#include "Product.h"
#include "../Manager.h"

using namespace std;

// 저장소
namespace ProductManagerConstants{
    const string RESOURCE = DIR_DATABASE + "product_list.csv";
}

class ProductManager : Manager
{
public:
    ProductManager();
    ~ProductManager();
    ProductManager(const ProductManager& other);
        
    // 데이터 관리 
    const bool add(const Product& product);
    const bool remove(const unsigned int id);
    const Product* getByIdOrNull(const unsigned int id) const;

    const bool contains(const unsigned int id) const;

    // 저장소 관리
    void load();

    // View 관리
    const bool displayMenu();
    void displayInfo() const;
    void inputItem();

private:
    void appendToFile(const Product& product) const;
    void removeFromFile(const unsigned int id) const;
    const unsigned int generateId() const;
    // 멤버변수
    map<unsigned int, Product*> mProductMap;
};

#endif // PRODUCT_MANAGER_H