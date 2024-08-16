#include "ProductManager.h"
#include "Product.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

/* ProductManager 클래스의 생성자
 CategoryManager객체를 참조로 받고, 멤버변수로 초기화*/
ProductManager::ProductManager(CategoryManager& categoryManager) 
    : mCategoryManager(categoryManager){
    loadProductsFromFile(); // 프로그램이 시작 시 파일 로드
}

// ProductManager 클래스의 소멸자
ProductManager::~ProductManager() {
    saveProductsToFile(); // 상품 데이터 파일에 저장
    for (const auto& plist : mProductMap) { 
        delete plist.second; // 상품 객체 메모리 해제
    }
}

void ProductManager::loadProductsFromFile() {
    std::ifstream file("products.txt");
    if (!file.is_open()) {
        cerr << "products.txt 파일 열기 오류" << endl;
        return;
    }

    while (file.peek() != EOF) {
        std::vector<std::string> row = parseCSV(file, ',');
        if (row.size() == 5) { // (id, 카테고리, 이름, 가격, 수량)
            try {
                int id = std::stoi(row[0]);
                int price = std::stoi(row[2]);
                int quantity = std::stoi(row[3]);
                string category = row[4];
                Product* product = new Product(id, category, row[1], price, quantity);
                mProductMap[id] = product;

                //  CategoryManager에서 해당 카테고리 찾아서 상품을 카테고리에 추가
                Category* cat = mCategoryManager.getCategory(category);
                if (cat) {
                    cat->addProduct(product);
                }
                else {
                    std::cerr << "카테고리 " << category << " 를 찾을 수 없습니다. 상품 : " << row[1] << std::endl;
                }
            }
            catch (const std::invalid_argument&) {
                //std::cerr << "products.txt에서 잘못된 데이터 형식" << std::endl;
            }
            catch (const std::out_of_range&) {
                //std::cerr << "products.txt에서 범위를 벗어난 값 << std::endl;
            }
        }
        else if (!row.empty()) {
            //std::cerr << "products.txt에서 잘못된 데이터 형식" << std::endl;
        }
    }
    file.close();
}

// 상품 데이터를 파일에 저장하는 함수
void ProductManager::saveProductsToFile() {
    std::ofstream file("products.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening products.txt for saving data" << std::endl;
        return;
    }

    for (const auto& plist : mProductMap) {
        Product* product = plist.second;
        file << product->getId() << ',' << product->getCategory() << ',' << product->getName() << ','
            << product->getPrice() << ',' << product->getQuantity() << std::endl;
    }
    file.close();
}

// CSV 형식의 데이터를 파싱하는 함수
std::vector<std::string> ProductManager::parseCSV(std::istream& file, char delimiter) {
    std::stringstream ss;
    std::vector<std::string> row;
    std::string t = " \n\r\t";

    while (file.peek() != EOF) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            std::string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}
// 새로운 상품 ID를 생성하는 함수
int ProductManager::makeId() {
    if (mProductMap.empty()) return 1;
    return mProductMap.rbegin()->first + 1;
}

void ProductManager::addProduct(const string& categoryName, const string& name, int price, int quantity) {
    // [mProductList] first : id, second : product*
    for (auto& pair : mProductMap) {
        Product* product = pair.second;
        // 동일 상품인 경우 수량 누적
        if (product->getName() == name && product->getPrice() == price) {
            product->setQuantity(product->getQuantity() + quantity);
            cout << "Product updated: " << name << endl;
            return;
        }
    }
    int id = makeId();
    // 새로운 상품 객체 생성
    Product* product = new Product(id, categoryName, name, price, quantity);
    // mProductList에 객체 추가
    mProductMap[id] = product;

    // 카테고리 확인 및 추가
    Category* category = mCategoryManager.getCategory(categoryName);
    if (category) {
        category->addProduct(product);
    }
    else {
        cout << "해당 카테고리는 존재하지 않습니다. 카테고리를 추가하시겠습니까? (Y/N) : ";
        char respones;
        cin >> respones;
        if (respones == 'y' || respones == 'Y') {
            mCategoryManager.addCategory(categoryName);
            Category* newCategory = mCategoryManager.getCategory(categoryName);
            if (newCategory) {
                newCategory->addProduct(product); // 새 카테고리에 상품을 추가
            }
        }
        else {
            delete product;
            cout << "상품을 추가하지 않았습니다. 카테고리를 추가해주세요." << endl;
        }
    }

    std::cout << "상품이 추가되었습니다: " << name << endl;
}
// 상품 ID로 상품을 검색하는 함수
Product* ProductManager::searchProduct(int id) const{
    auto it = mProductMap.find(id);

    // 상품이 존재하는 경우
    if (it != mProductMap.end()) {
        return it->second;
    }
    return nullptr;
}

// 주어진 ID를 가진 상품을 삭제하는 함수
void ProductManager::deleteProduct(int id) {
    Product* product = searchProduct(id);
    if (product) {
        // 상품의 카테고리를 가져옴
        Category* category = mCategoryManager.getCategory(product->getCategory());
        if (category) {
            // 카테고리에서도 상품을 삭제
            category->deleteProduct(id);
        }
        delete product; // 상품 객체 삭제
        mProductMap.erase(id);
        cout << "상품 ID :" << id << " 삭제되었습니다. " << endl;
    }
    else {
        cerr << "상품 ID : " << id << " 찾을 수 없습니다." << endl;
    }
}
// 모든 상품의 정보를 출력하는 함수
void ProductManager::displayProducts() const{
    if (mProductMap.empty()) {
        cout << "상품이 존재하지 않습니다. " << endl;
        return;
    }
    for (const auto& product : mProductMap) {
        product.second->displayInfo(); // 상품 객체의 정보 출력
    }
}

// 사용자 메뉴 표시 함수
bool ProductManager::displayMenu() {
    int choice, id;
    string categoryName, name;
    int price;
    int quantity;

    // 메뉴 UI 시작
    cout << "\n===================================" << endl;
    cout << "         상품 관리 시스템          " << endl;
    cout << "===================================" << endl;

    // 메뉴 옵션 출력
    cout << "| 1. 상품 목록 보기               |" << endl;
    cout << "| 2. 상품 추가                    |" << endl;
    cout << "| 3. 상품 삭제                    |" << endl;
    cout << "| 4. 종료                         |" << endl;
    cout << "===================================" << endl;

    cout << " 선택을 입력하세요: ";
    cin >> choice;
    cout << "===================================" << endl;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << " 잘못된 입력입니다. 다시 시도하세요." << endl;
        return true;
    }

    switch (choice) {
    case 1:
        cout << "\n****** 상품 목록 보기 ******" << endl;
        displayProducts();
        cout << "****************************" << endl;
        break;

    case 2:
        cin.ignore();
        cout << "\n****** 상품 추가 ******" << endl;
        cout << " 상품 이름을 입력하세요: "; getline(cin, name);
        cout << " 상품 가격을 입력하세요: "; cin >> price;
        cout << " 상품 수량을 입력하세요: "; cin >> quantity;
        cin.ignore();
        cout << " 상품 카테고리를 입력하세요: "; getline(cin, categoryName);
        addProduct(categoryName, name, price, quantity);
        cout << " 상품이 성공적으로 추가되었습니다!" << endl;
        cout << "****************************" << endl;
        break;

    case 3:
        cout << "\n****** 상품 삭제 ******" << endl;
        while (true) {
            cout << " 삭제할 상품의 ID를 입력하세요: "; cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << " 잘못된 ID입니다. 다시 시도하세요." << endl;
            }
            else {
                deleteProduct(id);
                break;
            }
        }
        cout << "****************************" << endl;
        break;

    case 4:
        return false;

    default:
        cerr << " 잘못된 선택입니다. 다시 시도하세요." << endl;
        break;
    }
    return true;
}
