#include "Category.h"

Category::Category(const std::string& category)
    : mCategory(category)
{
}

const std::string& Category::getName() const {
    return mCategory;
}

void Category::addProduct(Product* product) {
    mProducts.push_back(product);
}

void Category::removeProduct(Product* product) {
    auto it = std::remove(mProducts.begin(), mProducts.end(), product);
    if (it != mProducts.end()) {
        mProducts.erase(it, mProducts.end());
    }
}

const vector<Product*>& Category::getProducts() const {
    return mProducts;
}

