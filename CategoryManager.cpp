#include "CategoryManager.h"
#include "Category.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
// ������: ��ü�� ������ �� ī�װ� ������ ���Ͽ��� �ε�
CategoryManager::CategoryManager()
{
    loadCategoriesFromFile();
}
// �Ҹ���: ��ü�� ������ �� ī�װ� ������ ���Ͽ� ����
CategoryManager::~CategoryManager()
{
    saveCategoriesToFile();
    for (const auto& category : mCategoryMap) {
        delete category.second; // ī�װ� ��ü �޸� ����
    }
}

// ī�װ��� �߰��ϴ� �Լ�
void CategoryManager::addCategory(const string& categoryName)
{
    if (mCategoryMap.find(categoryName) == mCategoryMap.end()) { // ī�װ� �������� ������,
        mCategoryMap[categoryName] = new Category(categoryName);
        cout << "ī�װ� �߰� : " << categoryName << endl;
    }
    else {
        cout << categoryName << " ī�װ��� �̹� �����մϴ�." << endl;
    }
}
// ī�װ��� �����ϴ� �Լ�
void CategoryManager::deleteCategory(const string& categoryName)
{
    auto it = mCategoryMap.find(categoryName);
    if (it != mCategoryMap.end()) {
        delete it->second;
        mCategoryMap.erase(it);
        cout << "ī�װ� : " << categoryName << " ����" << endl;
    }
}
// ī�װ� �̸����� ī�װ� �˻��Ͽ� ��ȯ�ϴ� �Լ�
Category* CategoryManager::getCategory(const string& categoryName) const 
{
    auto it = mCategoryMap.find(categoryName);
    if (it != mCategoryMap.end()) {
        return it->second;
    }
    return nullptr;
}

void CategoryManager::displayCategories() const 
{
    if (mCategoryMap.empty()) {
        cout << "ī�װ��� �������� �ʽ��ϴ�" << endl;
        return;
    }
    cout << "ī�װ�: ";  
    bool first = true;

    for (const auto& category : mCategoryMap) {
        if (!first) {
            cout << ", ";  // ù ��° ���� ī�װ� �տ� ��ǥ �߰�
        }
        cout << category.first;
        first = false;
    }
    cout << endl;
}


void CategoryManager::loadCategoriesFromFile() 
{
    std::ifstream file("categories.txt");
    if (!file.is_open()) {
        std::cerr << "categories.txt ������ �� �� �����ϴ�" << std::endl;
        return;
    }

    while (file.peek() != EOF) {
        std::vector<std::string> categories = parseCSV(file, ',');
        for (const auto& category : categories) {
            std::string trimmedCategory = category;
            // �յ� ���� ����
            trimmedCategory.erase(0, trimmedCategory.find_first_not_of(" \n\r\t"));
            trimmedCategory.erase(trimmedCategory.find_last_not_of(" \n\r\t") + 1);

            if (!trimmedCategory.empty()) {
                addCategory(trimmedCategory);  // ī�װ� �߰�
            }
        }
    }
    file.close();
}


void CategoryManager::saveCategoriesToFile() const 
{
    std::ofstream file("categories.txt");
    if (!file.is_open()) {
        std::cerr << "categories.txt ������ �� �� �����ϴ�" << std::endl;
        return;
    }

    bool first = true; // ù ��° �׸� ���� ��ǥ�� ���� �ʱ� ���� ���
    for (const auto& pair : mCategoryMap) {
        if (!first) {
            file << ','; // ù ��° �׸��� �ƴϸ� ��ǥ �߰�
        }
        first = false;
        // ī�װ� �̸��� ���Ͽ� ��
        file << pair.first;
    }
    file << std::endl;
    file.close();
}


std::vector<std::string> CategoryManager::parseCSV(std::istream& file, char delimiter) 
{
    std::stringstream ss;
    std::vector<std::string> row;
    std::string t = " \n\r\t"; // ����, �� �ٲ�, ���� �����ϱ� ���� ���ڿ�

    while (file.peek() != EOF) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            std::string s = ss.str();
            s.erase(0, s.find_first_not_of(t)); // ���� ���� ����
            s.erase(s.find_last_not_of(t) + 1); // ���� ���� ����
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break; // �� �ٲ� ������ ��� ���� ����
        }
        else {
            ss << c;
        }
    }
    // ������ �׸��� �����ڷ� ������ �ʴ� ��� ó��
    if (!ss.str().empty()) {
        std::string s = ss.str();
        s.erase(0, s.find_first_not_of(t)); // ���� ���� ����
        s.erase(s.find_last_not_of(t) + 1); // ���� ���� ����
        row.push_back(s);
    }

    return row;
}
