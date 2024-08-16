#include "Store.h"
#include <iostream>

// ������ : Ŭ���̾�Ʈ �Ŵ���,��ǰ �Ŵ���, ī�װ� �Ŵ��� �ʱ�ȭ
Store::Store(ClientManager& cm, ProductManager& pm, CategoryManager& cmg)
    : mClientManager(cm), mProductManager(pm), mCategoryManager(cmg) {}

Store::~Store() {}


// ��ǰ�� �Ǹ��ϴ� �Լ�
void Store::sellProduct(int clientId, int productId) {
    Client* client = mClientManager.searchClient(clientId);
    Product* product = mProductManager.searchProduct(productId);

    // Ŭ���̾�Ʈ, ��ǰ, ��ǰ������ 0�̻��� ���
    if (client && product && product->getQuantity() > 0) {

        // ���� ��� ���� 
        PurchaseRecord record;
        record.clientId = clientId;
        record.clientName = client->getName();
        record.productId = productId;
        record.productName = product->getName();
        record.categoryName = mCategoryManager.getCategory(product->getCategory())->getName();
        //record.purchaseTime = getCurrentTime();
        mPurchaseHistoryVec.push_back(record);

        // ��ǰ�� ��� ����
        product->setQuantity(product->getQuantity() - 1);
        std::cout << "���� �Ϸ�: " << client->getName() << "���� " << product->getName() << "��(��) �����ϼ̽��ϴ�." << std::endl;
    }
    else {
        std::cerr << "������ �� �����ϴ�. �� �Ǵ� ��ǰ�� ��ȿ���� �ʰų� ��� �����մϴ�." << std::endl;
    }
}
// ��ǰ�� ��� ������Ʈ�ϴ� �Լ�
void Store::updateStock(int productId, int quantity) {
    Product* product = mProductManager.searchProduct(productId);
    if (product) {
        product->setQuantity(quantity);
        std::cout << "��ǰ ID " << productId << "�� ��� " << quantity << "�� ������Ʈ�Ǿ����ϴ�." << std::endl;
    }
    else {
        std::cerr << "��ȿ���� ���� ��ǰ ID�Դϴ�." << std::endl;
    }
}

void Store::displayPurchaseHistory() const {
    if (mPurchaseHistoryVec.empty()) {
        std::cout << "���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� ����:" << endl;
    for (const auto& record : mPurchaseHistoryVec) {
        std::cout << "�� ID: " << record.clientId
            << ", �� �̸�: " << record.clientName
            << ", ī�װ�: " << record.categoryName
            << ", ��ǰ ID: " << record.productId
            << ", ��ǰ �̸�: " << record.productName << endl;
            //<< ", ���� �ð�: " << record.purchaseTime << endl;
    }
}
