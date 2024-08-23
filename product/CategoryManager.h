#ifndef CATEGORY_MANAGER_H
#define CATEGORY_MANAGER_H

#include "../include/BaseManager.h"
#include "Category.h"

class CategoryManager : public BaseManager<Category>
{
public:
    // �����ڿ� �Ҹ���
    CategoryManager(const string& resourcePath);
    CategoryManager();
    virtual ~CategoryManager();

    // ī�װ� ���� ���
    void addCategory(const string& categoryName);
    void deleteCategory(const string& categoryName);
    void displayCategories() const;
    Category* getCategory(const string& categoryName) const;
};

#endif // CATEGORY_MANAGER_H
