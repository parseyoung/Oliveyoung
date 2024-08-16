#ifndef STORE_H
#define STORE_H
#include "ProductManager.h"
#include "ClientManager.h"
#include "CategoryManager.h"
#include <unordered_map>
#include <vector>
#include <string>

struct PurchaseRecord {
    int clientId; // �� id
    string clientName; // �� �̸�
    int productId; // ��ǰ id
    string productName; // ��ǰ �̸�
    string categoryName; // ī�װ� �̸�
    string purchaseTime; // ���� �ð�
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
    vector<PurchaseRecord> mPurchaseHistoryVec; // ���ų���
};


#endif // STORE_H
