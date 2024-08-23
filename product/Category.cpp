#include "Category.h"
#include "Product.h" 
#include <iostream>

Category::Category(const string& name)
    : mName(name), mId(mId) {
}

Category::~Category() {
    for (const auto& product : mProductsMap) {
        delete product.second;
    }
}

void Category::addProduct(Product* product) {
    int id = product->getId();
    auto it = mProductsMap.find(id);
    if (it != mProductsMap.end()) {
        Product* existingProduct = it->second;
        existingProduct->setQuantity(existingProduct->getQuantity() + product->getQuantity());
        delete product;
    }
    else {
        mProductsMap[id] = product;
    }
}

void Category::deleteProduct(int id) {
    auto it = mProductsMap.find(id);
    if (it != mProductsMap.end()) {
        delete it->second;
        mProductsMap.erase(it);
        std::cout << "Product ID " << id << " removed from category " << mName << std::endl;
    }
    else {
        std::cerr << "Product ID " << id << " not found in category " << mName << std::endl;
    }
}

Product* Category::searchProduct(int id) const {
    auto it = mProductsMap.find(id);
    if (it != mProductsMap.end()) {
        return it->second;
    }
    return nullptr;
}

void Category::displayProducts() const {
    if (mProductsMap.empty()) {
        std::cout << "No products in category: " << mName << std::endl;
        return;
    }

    for (const auto& product : mProductsMap) {
        product.second->displayInfo();
    }
}

std::string Category::getName() const {
    return mName;
}

unsigned int Category::getId() const {
    return mId;
}