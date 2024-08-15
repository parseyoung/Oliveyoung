// Store.cpp
#include "Store.h"
#include <iostream>

Store::Store(ClientManager& cm, ProductManager& pm, CategoryManager& cmg)
    : clientManager(cm), productManager(pm), categoryManager(cmg) {}

Store::~Store() {}

void Store::sellProduct(int clientId, int productId) {
    // Get client and product information
    Client* client = clientManager.searchClient(clientId);
    Product* product = productManager.searchProduct(productId);

    if (client && product && product->getQuantity() > 0) {
        // Record the purchase
        PurchaseRecord record;
        record.clientId = clientId;
        record.clientName = client->getName();
        record.productId = productId;
        record.productName = product->getName();
        purchaseHistory.push_back(record);

        // Update product stock
        product->setQuantity(product->getQuantity() - 1);
        std::cout << "구매 완료: " << client->getName() << "님이 " << product->getName() << "을(를) 구매하셨습니다." << std::endl;
    }
    else {
        std::cerr << "구매할 수 없습니다. 고객 또는 제품이 유효하지 않거나 재고가 부족합니다." << std::endl;
    }
}

void Store::updateStock(int productId, int newStock) {
    Product* product = productManager.searchProduct(productId);
    if (product) {
        product->setQuantity(newStock);
        std::cout << "상품 ID " << productId << "의 재고가 " << newStock << "로 업데이트되었습니다." << std::endl;
    }
    else {
        std::cerr << "유효하지 않은 상품 ID입니다." << std::endl;
    }
}

void Store::displayPurchaseHistory() const {
    if (purchaseHistory.empty()) {
        std::cout << "구매 내역이 없습니다." << std::endl;
        return;
    }

    std::cout << "구매 내역:" << std::endl;
    for (const auto& record : purchaseHistory) {
        std::cout << "고객 ID: " << record.clientId
            << ", 고객 이름: " << record.clientName
            << ", 상품 ID: " << record.productId
            << ", 상품 이름: " << record.productName << std::endl;
    }
}
