#ifndef STORE_MANAGER_H
#define STORE_MANAGER_H

#include "Store.h"
#include "../product/Product.h"
#include "../product/ProductManager.h"
#include "../client/ClientManager.h"
#include "../database/Constants.h"
#include "../Manager.h"

// 저장소
const string STOCK_INFO = DIR_DATABASE + "stock_list.csv";
const string PURCHASE_HISTORY = DIR_DATABASE + "purchase_history.csv";

class StoreManager : Manager
{
public:
    StoreManager(Store& store, ProductManager& productManager, ClientManager& clientManager);
    ~StoreManager();
    StoreManager(const StoreManager& other);

// 데이터 관리 
    // 재고
    void setStockInfo();

    const bool setQuantity(const Product& product, const unsigned int quantity);
    const bool setAvailability(const Product& product, const bool availability);
    
    // 판매 
    const bool sell(const unsigned int productId, const unsigned int clientId);

// 저장소 관리
    void load();

// View 관리
    const bool displayMenu();

private:
    void handleSellProduct();
    void displayInfo() const;//displayStockInfo
    


    void appendToFile(const unsigned int productId, const StockInfo& stockInfo) const;
    void removeFromFile(const unsigned int id) const;
    void updateStockInfoInFile(const unsigned int productId, const StockInfo& updatedStockInfo) const;

    void displayPurchaseHistory() const;
    void appendPurchaseToFile(unsigned int productId, unsigned int clientId) const;
    void recordPurchase(const unsigned int productId, const unsigned int clientId) const;

    Store& mStore;  
    ProductManager& mProductManager; 
    ClientManager& mClientManager;
};

#endif // STORE_MANAGER_H
