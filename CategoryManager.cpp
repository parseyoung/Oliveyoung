#include "CategoryManager.h"
#include "Category.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
// 생성자: 객체가 생성될 때 카테고리 정보를 파일에서 로드
CategoryManager::CategoryManager()
{
    loadCategoriesFromFile();
}
// 소멸자: 객체가 삭제될 때 카테고리 정보를 파일에 저장
CategoryManager::~CategoryManager()
{
    saveCategoriesToFile();
    for (const auto& category : mCategoryMap) {
        delete category.second; // 카테고리 객체 메모리 해제
    }
}

// 카테고리를 추가하는 함수
void CategoryManager::addCategory(const string& categoryName)
{
    if (mCategoryMap.find(categoryName) == mCategoryMap.end()) { // 카테고리 존재하지 않으면,
        mCategoryMap[categoryName] = new Category(categoryName);
        cout << "카테고리 추가 : " << categoryName << endl;
    }
    else {
        cout << categoryName << " 카테고리는 이미 존재합니다." << endl;
    }
}
// 카테고리를 삭제하는 함수
void CategoryManager::deleteCategory(const string& categoryName)
{
    auto it = mCategoryMap.find(categoryName);
    if (it != mCategoryMap.end()) {
        delete it->second;
        mCategoryMap.erase(it);
        cout << "카테고리 : " << categoryName << " 삭제" << endl;
    }
}
// 카테고리 이름으로 카테고리 검색하여 반환하는 함수
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
        cout << "카테고리가 존재하지 않습니다" << endl;
        return;
    }
    cout << "카테고리: ";  
    bool first = true;

    for (const auto& category : mCategoryMap) {
        if (!first) {
            cout << ", ";  // 첫 번째 이후 카테고리 앞에 쉼표 추가
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
