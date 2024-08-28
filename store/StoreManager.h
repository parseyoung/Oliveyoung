#ifndef STORE_MANAGER_H
#define STORE_MANAGER_H

#include <vector>

#include "Store.h"
#include "../product/Product.h"
#include "../product/ProductManager.h"
#include "../client/ClientManager.h"
#include "../database/Constants.h"
#include "../logger/Logger.h"
#include "../observer/Observer.h"


// 저장소
const string STOCK_INFO = DIR_DATABASE + "stock_list.csv";
const string PURCHASE_HISTORY = DIR_DATABASE + "purchase_history.csv";

class StoreManager:public Observer
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
    void loadStockInfo();

// View 관리
    const bool displayMenu();

//subject
    void update(unsigned int id);

private:
    void handleSellProduct();
    void displayStockInfo() const;
    void displayPurchaseHistory() const;


    vector<string> parseCSV(istream& stream, char delimiter);

    void appendStockInfoToFile(const unsigned int productId, const StockInfo& stockInfo) const;
    void removeStockInfoFromFile(const unsigned int id) const;
    void updateStockInfoInFile(const unsigned int productId, const StockInfo& updatedStockInfo) const;

    void appendPurchaseToFile(unsigned int productId, unsigned int clientId) const;

    void recordPurchase(const unsigned int productId, const unsigned int clientId) const;


    Store& mStore;  
    ProductManager& mProductManager;  
    ClientManager& mClientManager;

    static Logger logger;
};

#endif // STORE_MANAGER_H

