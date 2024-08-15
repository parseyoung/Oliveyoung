#include "ProductManager.h"
#include "Product.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

ProductManager::ProductManager(CategoryManager& categoryManager) 
    : mCategoryManager(categoryManager){
    loadProductsFromFile();
}

ProductManager::~ProductManager() {
    saveProductsToFile();
    for (const auto& plist : mProductList) {
        delete plist.second;
    }
}

void ProductManager::loadProductsFromFile() {
    std::ifstream file("products.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening products.txt" << std::endl;
        return;
    }

    while (file.peek() != EOF) {
        std::vector<std::string> row = parseCSV(file, ',');
        if (row.size() == 5) { // Expecting 4 columns
            try {
                int id = std::stoi(row[0]);
                int price = std::stoi(row[2]);
                int quantity = std::stoi(row[3]);
                string category = row[4];
                Product* product = new Product(id, category, row[1], price, quantity);
                mProductList[id] = product;

                Category* cat = mCategoryManager.getCategory(category);
                if (cat) {
                    cat->addProduct(product);
                }
                else {
                    std::cerr << "Category " << category << " not found for product " << row[1] << std::endl;
                }
            }
            catch (const std::invalid_argument&) {
                std::cerr << "Invalid data format in products.txt" << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cerr << "Value out of range in products.txt" << std::endl;
            }
        }
        else if (!row.empty()) {
            std::cerr << "Incorrect data format in products.txt" << std::endl;
        }
    }
    file.close();
}

void ProductManager::saveProductsToFile() {
    std::ofstream file("products.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening products.txt for saving data" << std::endl;
        return;
    }

    for (const auto& plist : mProductList) {
        Product* product = plist.second;
        file << product->getId() << ',' << product->getCategory() << ',' << product->getName() << ','
            << product->getPrice() << ',' << product->getQuantity() << std::endl;
    }
    file.close();
}


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

int ProductManager::makeId() {
    if (mProductList.empty()) return 1;
    return mProductList.rbegin()->first + 1;
}

void ProductManager::addProduct(const string& categoryName, const string& name, int price, int quantity) {
    // [mProductList] first : id, second : product*
    for (auto& pair : mProductList) {
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
    mProductList[id] = product;

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
                newCategory->addProduct(product);
            }
        }
        else {
            delete product;
            cout << "상품을 추가하지 않았습니다. 카테고리를 추가해주세요." << endl;
        }
    }

    std::cout << "Product added: " << name << endl;
}

Product* ProductManager::searchProduct(int id) const{
    auto it = mProductList.find(id);

    // 상품이 존재하는 경우
    if (it != mProductList.end()) {
        return it->second;
    }
    return nullptr;
}

void ProductManager::deleteProduct(int id) {
    Product* product = searchProduct(id);
    if (product) {
        Category* category = mCategoryManager.getCategory(product->getCategory());
        if (category) {
            category->deleteProduct(id);
        }
        delete product;
        mProductList.erase(id);
        std::cout << "Product ID " << id << " deleted" << std::endl;
    }
    else {
        std::cerr << "Product ID " << id << " not found" << std::endl;
    }
}

void ProductManager::displayProducts() const{
    if (mProductList.empty()) {
        std::cout << "No products to display" << std::endl;
        return;
    }
    for (const auto& prod : mProductList) {
        prod.second->displayInfo();
    }
}

bool ProductManager::displayMenu() {
    int choice, id;
    string categoryName, name;
    int price;
    int quantity;
    cout << std::endl;
    cout << "Product Menu:\n";
    cout << "1. Display Products\n";
    cout << "2. Add Product\n";
    cout << "3. Delete Product\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cerr << "Invalid input, try again" << endl;
        return true;
    }

    switch (choice) {
    case 1:
        displayProducts();
        break;

    case 2:
        cin.ignore();
        cout << "Enter product name: "; getline(cin, name);
        cout << "Enter product price: "; cin >> price;
        cout << "Enter product quantity: "; cin >> quantity;
        std::cin.ignore();
        cout << "Enter product category: "; getline(cin, categoryName);
        addProduct(categoryName, name, price, quantity);
        break;

    case 3:
        while (true) {
            std::cout << "Enter ID to delete: "; cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cerr << "Invalid ID, try again" << endl;
            }
            else {
                deleteProduct(id);
                break;
            }
        }
        break;

    case 4:
        return false;

    default:
        cerr << "Invalid choice. Try again." << endl;
        break;
    }
    return true;
}
