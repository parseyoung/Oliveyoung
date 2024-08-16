#include "Category.h"
#include <iostream>

// Category 생성자, 카테고리 이름 초기화
Category::Category(const string& name)
	: mName(name) {} 

// Category 소멸자
Category::~Category()
{
	// 카테고리 내 모든 상품 메모리 해제
	for (const auto& product : mProductsMap) {
		delete product.second; 
	}
}

// 카테고리에 상품 추가 함수
void Category::addProduct(Product* product)
{
	int id = product->getId();
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) { // 이미 존재하는 상품일 경우 수량 증가
		it->second->setQuantity(it->second->getQuantity() + product->getQuantity());
		delete product; // 상품 객체는 추가하지 않음
	}
	else {
		mProductsMap[id] = product; // 새 상품 추가
	}
}

// 카테고리에서 해당 ID가진 상품 삭제
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

// 상품 검색 함수
Product* Category::searchProduct(int id) const
{
	auto it = mProductsMap.find(id);
	if (it != mProductsMap.end()) {
		return it->second;
	}
	return nullptr;
}

// 카테고리 내 상품 목록 출력 함수
void Category::displayProducts() const
{
	if (mProductsMap.empty()) {
		cout << "카테고리 내 상품이 존재하지 않습니다. " << mName << endl;
		return;
	}

	for (const auto& product : mProductsMap) {
		product.second->displayInfo();
	}
}

// 카테고리 이름 반환 함수
string Category::getName() const
{
	return mName;
}