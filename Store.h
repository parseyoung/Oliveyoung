#ifndef STORE_H
#define STORE_H
#include "ProductManager.h"
#include "ClientManager.h"
#include "CategoryManager.h"
#include <unordered_map>
#include <vector>
#include <string>

struct PurchaseRecord {
    int clientId; // 고객 id
    string clientName; // 고객 이름
    int productId; // 상품 id
    string productName; // 상품 이름
    string categoryName; // 카테고리 이름
    string purchaseTime; // 구매 시간
};

class Store
{
public:
    Store(ClientManager& cm, ProductManager& pm, CategoryManager& catm);
   
    void updateStock(int productId, int quantity);
    void sellProduct(int clientId, int productId);
    void displayPurchaseHistory() const;
    ~Store();

private:

    ClientManager& mClientManager;
    ProductManager& mProductManager;
    CategoryManager& mCategoryManager;
    vector<PurchaseRecord> mPurchaseHistoryVec; // 구매내역
};


#endif // STORE_H
