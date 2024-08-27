#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>

#include "ProductManager.h"
#include "Product.h"
#include "Category.h"

using namespace std;

namespace ProductManagerConstants {
    const string RESOURCE = DIR_DATABASE + "product_list.csv";
}

Logger ProductManager::logger("ProductManager");

ProductManager::ProductManager() 
    : BaseManager<Product>(ProductManagerConstants::RESOURCE)
{
}

// View 관리
const bool ProductManager::displayMenu()
{
    enum MenuOptions { DISPLAY_PRODUCT_LIST = 1, INPUT_PRODUCT, DELETE_PRODUCT, VIEW_BY_CATEGORY, QUIT_PROGRAM };

    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. Input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. View Products by Category                " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you want to do? ";

    int id;
    int menu;
    cin >> menu;
    string categoryName;

    switch (menu) {
    case DISPLAY_PRODUCT_LIST:
        displayItemsInfo();
        cin.ignore(); // Ignore leftover newline character
        getchar();   // Wait for user to press Enter
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
        cin >> id;
        remove(id);
        break;
    case VIEW_BY_CATEGORY:
        cout << "Enter category name: ";
       
        cin >> categoryName;
        displayProductsByCategory(categoryName);
        break;
    case QUIT_PROGRAM:
        return true;
    default:
        cout << "Please enter a number between " << DISPLAY_PRODUCT_LIST << " and " << QUIT_PROGRAM << "." << endl;
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
    cout << "return to menu: enter any key" << endl;
}


void ProductManager::inputItem()
{
    string name;
    int priceInput;
    string categoryInput;
    cout << "name : "; cin >> name;
    cout << "price : "; cin >> priceInput;
    cout << "category : "; cin >> categoryInput;

    try {
        Price price(priceInput);

        // 카테고리 이름으로 카테고리 객체를 찾거나 생성
        Category& category = mCategoryMap[categoryInput];

        // Product 객체 생성
        Product newProduct(generateId(), name, price, &category); // Category의 주소를 전달

        add(newProduct);

        // 카테고리에 상품 추가
        category.addProduct(&newProduct);

        logger.info("Product added: Name=" + name + ", Price=" + to_string(priceInput) + ", Category=" + categoryInput);

    }
    catch (const invalid_argument& e) {
        logger.error("Failed to add product: Name=" + name + ", Error=" + string(e.what()));
    }
}


void ProductManager::displayProductsByCategory(const string& categoryName) const
{
    const Category* category = findCategoryByName(categoryName);
    if (category) {
        cout << "Category: " << category->getName() << endl;
        for (const auto& product : category->getProducts()) {
            cout << product->toString() << ", ";
        }
        cout << endl;
    }
    else {
        cout << "카테고리를 찾을 수 없습니다." << endl;
    }
}

const Category* ProductManager::findCategoryByName(const string& categoryName) const
{
    auto it = mCategoryMap.find(categoryName);
    if (it != mCategoryMap.end()) {
        return &it->second;
    }
    return nullptr;
}

