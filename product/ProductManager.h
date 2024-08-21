#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <map>

#include "../database/Constants.h"
#include "Product.h"
#include "../Validation/BaseEntity.h"

using namespace std;

// 저장소
namespace ProductManagerConstants {
    const string RESOURCE = DIR_DATABASE + "product_list.csv";
}

class ProductManager : public BaseEntity<Product>
{
public:
    ProductManager();
    ~ProductManager();
    ProductManager(const ProductManager& other);
        
    // 데이터 관리 
    bool add(const Product& product) override;
    bool remove(const unsigned int id) override;
    const Product* getByIdOrNull(const unsigned int id) const;

    const bool contains(const unsigned int id) const;

    // 저장소 관리
    void load();

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();

private:
    unsigned int generateId() const;
    
    vector<string> parseCSV(istream& fin, char delimiter);
    void appendToFile(const Product& product) const override;
    void removeFromFile(const unsigned int id) const override;

    // 멤버변수
    map<unsigned int, Product*> mProductMap;
};

#endif // PRODUCT_MANAGER_H