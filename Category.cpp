#include "Category.h"
#include <iostream>

// Category ������, ī�װ� �̸� �ʱ�ȭ
Category::Category(const string& name)
	: mName(name) {} 

// Category �Ҹ���
Category::~Category()
{
	// ī�װ� �� ��� ��ǰ �޸� ����
	for (const auto& product : mProductsMap) {
		delete product.second; 
	}
}

// ī�װ��� ��ǰ �߰� �Լ�
void Category::addProduct(Product* product)
{
	int id = product->getId();
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) { // �̹� �����ϴ� ��ǰ�� ��� ���� ����
		it->second->setQuantity(it->second->getQuantity() + product->getQuantity());
		delete product; // ��ǰ ��ü�� �߰����� ����
	}
	else {
		mProductsMap[id] = product; // �� ��ǰ �߰�
	}
}

// ī�װ����� �ش� ID���� ��ǰ ����
void Category::deleteProduct(int id) {
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) {
		delete it->second; // ��ǰ�� �޸� ����
		mProductsMap.erase(it); // �ʿ��� ��ǰ ����
		std::cout << "Product ID " << id << " removed from category " << mName << std::endl;
	}
	else {
		std::cerr << "Product ID " << id << " not found in category " << mName << std::endl;
	}
}

// ��ǰ �˻� �Լ�
Product* Category::searchProduct(int id) const
{
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) {
		return it->second;
	}
	return nullptr;
}

// ī�װ� �� ��ǰ ��� ��� �Լ�
void Category::displayProducts() const
{
	if (mProductsMap.empty()) {
		cout << "ī�װ� �� ��ǰ�� �������� �ʽ��ϴ�. " << mName << endl;
		return;
	}

	for (const auto& product : mProductsMap) {
		product.second->displayInfo();
	}
}

// ī�װ� �̸� ��ȯ �Լ�
string Category::getName() const
{
	return mName;
}