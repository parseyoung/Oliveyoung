#include "CategoryManager.h"
#include <iostream>

CategoryManager::CategoryManager(const string& resourcePath)
    : BaseManager<Category>(resourcePath)
{
}

CategoryManager::~CategoryManager()
{
    // BaseManager�� �Ҹ��ڰ� �ڵ����� ȣ��Ǿ� �ڿ� ������
}

void CategoryManager::addCategory(const string& categoryName)
{
    // �̹� �����ϴ� ī�װ����� Ȯ��
    Category* existingCategory = getCategory(categoryName);
    if (existingCategory != nullptr) {
        cerr << "Category already exists: " << categoryName << endl;
        return;
    }

    // ���ο� ī�װ� �߰�
    unsigned int newId = generateId();
    Category newCategory(categoryName);
    if (add(newCategory)) {
        std::cout << "Added category: " << categoryName << endl;
    }
    else {
        std::cerr << "Failed to add category: " << categoryName << std::endl;
    }
}

void CategoryManager::deleteCategory(const string& categoryName)
{
    Category* category = getCategory(categoryName);
    if (category != nullptr) {
        unsigned int id = category->getId();
        if (remove(id)) {
            std::cout << "Deleted category with name: " << categoryName << std::endl;
        }
        else {
            std::cerr << "Failed to delete category with name: " << categoryName << std::endl;
        }
    }
    else {
        std::cerr << "Category not found with name: " << categoryName << std::endl;
    }
}

void CategoryManager::displayCategories() const
{
    if (mItemMap.empty()) {
        std::cout << "No categories available" << std::endl;
        return;
    }

    std::cout << "Categories:" << std::endl;
    for (const auto& pair : mItemMap) {
        std::cout << "ID: " << pair.first << ", Name: " << pair.second->getName() << std::endl;
    }
}

Category* CategoryManager::getCategory(const string& categoryName) const
{
    for (const auto& pair : mItemMap) {
        if (pair.second->getName() == categoryName) {
            return pair.second;
        }
    }
    return nullptr;
}
