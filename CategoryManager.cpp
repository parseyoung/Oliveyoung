#include "CategoryManager.h"
#include "Category.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

CategoryManager::CategoryManager()
{
    loadCategoriesFromFile();
}

CategoryManager::~CategoryManager()
{
    saveCategoriesToFile();
    for (const auto& pair : mCategoryMap) {
        delete pair.second;
    }
}

void CategoryManager::addCategory(const string& categoryName)
{
    if (mCategoryMap.find(categoryName) == mCategoryMap.end()) {
        mCategoryMap[categoryName] = new Category(categoryName);
        //cout << "Category added: " << categoryName << endl;
    }
    else {
        //cout << "Category already exists: " << categoryName << endl;
    }
}

void CategoryManager::deleteCategory(const string& categoryName)
{
    auto it = mCategoryMap.find(categoryName);
    if (it != mCategoryMap.end()) {
        delete it->second;
        mCategoryMap.erase(it);
        cout << "Category " << categoryName << " deleted" << endl;
    }
    else {
        cerr << "Category " << categoryName << " not found" << endl;
    }
}

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
        cout << "No categories to display" << endl;
        return;
    }
    cout << "Category: ";  
    bool first = true;

    for (const auto& pair : mCategoryMap) {
        if (!first) {
            cout << ", ";  // 첫 번째 이후 카테고리 앞에 쉼표 추가
        }
        cout << pair.first;
        first = false;
    }
    cout << endl;
}


void CategoryManager::loadCategoriesFromFile() 
{
    std::ifstream file("categories.txt");
    if (!file.is_open()) {
        std::cerr << "categories.txt 파일을 열 수 없습니다" << std::endl;
        return;
    }

    while (file.peek() != EOF) {
        std::vector<std::string> categories = parseCSV(file, ',');
        for (const auto& category : categories) {
            std::string trimmedCategory = category;
            // 앞뒤 공백 제거
            trimmedCategory.erase(0, trimmedCategory.find_first_not_of(" \n\r\t"));
            trimmedCategory.erase(trimmedCategory.find_last_not_of(" \n\r\t") + 1);

            if (!trimmedCategory.empty()) {
                addCategory(trimmedCategory);  // 카테고리 추가
            }
        }
    }
    file.close();
}


void CategoryManager::saveCategoriesToFile() const 
{
    std::ofstream file("categories.txt");
    if (!file.is_open()) {
        std::cerr << "categories.txt 파일을 열 수 없습니다" << std::endl;
        return;
    }

    bool first = true; // 첫 번째 항목에 대해 쉼표를 넣지 않기 위해 사용
    for (const auto& pair : mCategoryMap) {
        if (!first) {
            file << ','; // 첫 번째 항목이 아니면 쉼표 추가
        }
        first = false;
        // 카테고리 이름을 파일에 씀
        file << pair.first;
    }
    file << std::endl;
    file.close();
}


std::vector<std::string> CategoryManager::parseCSV(std::istream& file, char delimiter) 
{
    std::stringstream ss;
    std::vector<std::string> row;
    std::string t = " \n\r\t"; // 공백, 줄 바꿈, 탭을 제거하기 위한 문자열

    while (file.peek() != EOF) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            std::string s = ss.str();
            s.erase(0, s.find_first_not_of(t)); // 앞의 공백 제거
            s.erase(s.find_last_not_of(t) + 1); // 뒤의 공백 제거
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break; // 줄 바꿈 문자일 경우 루프 종료
        }
        else {
            ss << c;
        }
    }
    // 마지막 항목이 구분자로 끝나지 않는 경우 처리
    if (!ss.str().empty()) {
        std::string s = ss.str();
        s.erase(0, s.find_first_not_of(t)); // 앞의 공백 제거
        s.erase(s.find_last_not_of(t) + 1); // 뒤의 공백 제거
        row.push_back(s);
    }

    return row;
}
