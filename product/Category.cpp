#include "Category.h"

Category::Category(const string& name)
	: mName(name) {}

Category::Category(const Category& other)
    : mName(other.mName), mProduct(other.mProduct)
{
}

Category& Category::operator=(const Category& other)
{
    if (this != &other) {
        mName = other.mName;
        mProduct = other.mProduct;
    }
    return *this;
}

void Category::addProduct(Product* product)
{
	mProduct.push_back(product);
}

const vector<Product*>& Category::getProducts() const
{
	return mProduct;
}

const string& Category::getName() const
{
	return mName;
}

