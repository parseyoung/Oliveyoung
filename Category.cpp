#include "Category.h"
#include <iostream>

Category::Category(const string& name)
	: mName(name) {}

Category::~Category()
{
	for (const auto& pair : mProductsMap) {
		delete pair.second;
	}
}

void Category::addProduct(Product* product)
{
	int id = product->getId();
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) {
		it->second->setQuantity(it->second->getQuantity() + product->getQuantity());
		delete product;
	}
	else {
		mProductsMap[id] = product;
	}
}

void Category::deleteProduct(int id) {
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) {
		delete it->second; // 상품의 메모리 해제
		mProductsMap.erase(it); // 맵에서 상품 제거
		std::cout << "Product ID " << id << " removed from category " << mName << std::endl;
	}
	else {
		std::cerr << "Product ID " << id << " not found in category " << mName << std::endl;
	}
}

Product* Category::searchProduct(int id) const
{
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) {
		return it->second;
	}
	return nullptr;
}

void Category::displayProducts() const
{
	if (mProductsMap.empty()) {
		cout << "No products in category " << mName << endl;
		return;
	}

	for (const auto& pair : mProductsMap) {
		pair.second->displayInfo();
	}
}

string Category::getName() const
{
	return mName;
}