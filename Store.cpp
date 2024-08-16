#include "Store.h"
#include <iostream>

// 생성자 : 클라이언트 매니저,상품 매니저, 카테고리 매니저 초기화
Store::Store(ClientManager& cm, ProductManager& pm, CategoryManager& cmg)
    : mClientManager(cm), mProductManager(pm), mCategoryManager(cmg) {}

Store::~Store() {}


// 제품을 판매하는 함수
void Store::sellProduct(int clientId, int productId) {
    Client* client = mClientManager.searchClient(clientId);
    Product* product = mProductManager.searchProduct(productId);

    // 클라이언트, 제품, 제품수량이 0이상인 경우
    if (client && product && product->getQuantity() > 0) {

        // 구매 기록 생성 
        PurchaseRecord record;
        record.clientId = clientId;
        record.clientName = client->getName();
        record.productId = productId;
        record.productName = product->getName();
        record.categoryName = mCategoryManager.getCategory(product->getCategory())->getName();
        //record.purchaseTime = getCurrentTime();
        mPurchaseHistoryVec.push_back(record);

        // 제품의 재고 감소
        product->setQuantity(product->getQuantity() - 1);
        std::cout << "구매 완료: " << client->getName() << "님이 " << product->getName() << "을(를) 구매하셨습니다." << std::endl;
    }
    else {
        std::cerr << "구매할 수 없습니다. 고객 또는 제품이 유효하지 않거나 재고가 부족합니다." << std::endl;
    }
}
// 제품의 재고를 업데이트하는 함수
void Store::updateStock(int productId, int quantity) {
    Product* product = mProductManager.searchProduct(productId);
    if (product) {
        product->setQuantity(quantity);
        std::cout << "상품 ID " << productId << "의 재고가 " << quantity << "로 업데이트되었습니다." << std::endl;
    }
    else {
        std::cerr << "유효하지 않은 상품 ID입니다." << std::endl;
    }
}

void Store::displayPurchaseHistory() const {
    if (mPurchaseHistoryVec.empty()) {
        std::cout << "구매 내역이 없습니다." << std::endl;
        return;
    }

    std::cout << "구매 내역:" << endl;
    for (const auto& record : mPurchaseHistoryVec) {
        std::cout << "고객 ID: " << record.clientId
            << ", 고객 이름: " << record.clientName
            << ", 카테고리: " << record.categoryName
            << ", 상품 ID: " << record.productId
            << ", 상품 이름: " << record.productName << endl;
            //<< ", 구매 시간: " << record.purchaseTime << endl;
    }
}
