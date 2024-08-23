#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <map>

#include "ProductManager.h"
#include "Product.h"

using namespace std;

namespace ProductManagerConstants {
    const string RESOURCE = DIR_DATABASE + "product_list.csv";
}

ProductManager::ProductManager(CategoryManager& categoryManager)
    : BaseManager<Product>(ProductManagerConstants::RESOURCE), mCategoryManager(categoryManager) {
}

bool ProductManager::displayMenu() {
    enum MenuOptions {
        DISPLAY_PRODUCT_LIST = 1,
        INPUT_PRODUCT,
        DELETE_PRODUCT,
        DISPLAY_CATEGORIES,
        ADD_CATEGORY,
        DELETE_CATEGORY,
        QUIT_PROGRAM
    };

    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. Input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Display Categories                       " << endl;
    cout << "  5. Add Category                             " << endl;
    cout << "  6. Delete Category                          " << endl;
    cout << "  7. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";

    int menu;
    cin >> menu;
    switch (menu) {
    case DISPLAY_PRODUCT_LIST:
        displayItemsInfo();
        cin.ignore();
        cin.get();
        break;
    case INPUT_PRODUCT:
        cout << setw(45) << setfill('-') << "\n" << endl;
        cout << "Input Product (name)" << endl;
        cout << setw(45) << setfill('-') << "\n" << endl;
        inputItem();
        break;
    case DELETE_PRODUCT:
        cout << setw(45) << setfill('-') << "\n" << endl;
        cout << "Delete Product" << endl;
        cout << setw(45) << setfill('-') << "\n" << endl;
        displayItemsInfo();
        cout << "   Choose product id : ";
        int id;
        cin >> id;
        remove(id);
        break;
    case DISPLAY_CATEGORIES:
        displayCategories();
        break;
    case ADD_CATEGORY: {
        string name;
        cout << "Enter new category name: ";
        cin >> name;
        Category newCategory(name);
        mCategoryManager.addCategory(name); // CategoryManager에 추가
        break;
    }
    case DELETE_CATEGORY: {
        string name;
        cout << "Enter category name to delete: ";
        cin >> name;
        mCategoryManager.deleteCategory(name); // CategoryManager에서 삭제
        break;
    }
    case QUIT_PROGRAM:
        return true;
    default:
        cout << "Please enter a value between " << DISPLAY_PRODUCT_LIST << " and " << QUIT_PROGRAM << "." << endl;
        break;
    }

    return false;
}

void ProductManager::displayItemsInfo() const
{
    cout << "Product list" << endl;
    cout << endl << "  ID  |     Name     " << endl;
    for (const auto& it : mItemMap) {
        Product* product = it.second;
        cout << setw(5) << setfill('0') << right << product->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << product->getName() << endl;
        cout << setw(12) << setfill(' ') << product->getPrice().get() << endl;
        cout << setw(12) << setfill(' ') << product->getCategory().getName() << endl;
    }

    cout << endl;
    cout << "Return to menu: enter any key" << endl;
}

void ProductManager::inputItem() {
    string name;
    int priceInput;
    string categoryInput;
    cout << "name : "; cin >> name;
    cout << "price : "; cin >> priceInput;
    cout << "category : "; cin >> categoryInput;

    // 카테고리 확인
    Category* category = mCategoryManager.getCategory(categoryInput);
    if (category == nullptr) {
        cerr << "Category does not exist. Please add the category first." << endl;
        return;
    }

    try {
        Price price(priceInput);
        Product* product = new Product(generateId(), *category, name, price, StockInfo(0, true)); // Allocate dynamically
        add(*product); // Add the product to ProductManager
        category->addProduct(product); // 카테고리에 제품 추가
    }
    catch (const std::invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        cout << "Product creation failed. Please try again." << endl;
    }
}

void ProductManager::remove(int id) {
    auto it = mItemMap.find(id);
    if (it != mItemMap.end()) {
        Product* product = it->second;
        Category* category = mCategoryManager.getCategory(product->getCategory().getName());
        if (category) {
            category->deleteProduct(id); // Remove the product from the category
        }
        delete product; // Delete the product
        mItemMap.erase(it); // Remove from the map
        cout << "Product ID " << id << " removed." << endl;
    }
    else {
        cerr << "Product ID " << id << " not found." << endl;
    }
}

void ProductManager::displayCategories() const {
    mCategoryManager.displayCategories();
}


void ProductManager::addCategory(Category& category) {
    mCategoryManager.addCategory(category.getName()); // 카테고리 매니저에 추가
}

void ProductManager::removeCategory(const std::string& categoryName) {
    mCategoryManager.deleteCategory(categoryName); // 카테고리 매니저에서 삭제
}
