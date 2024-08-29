#include "Category.h"

Category::Category(const string& category)
    : mCategory(category)
{
}

const string& Category::getName() const {
    return mCategory;
}

void Category::addProduct(Product* product) {
    mProducts.push_back(product);
}


