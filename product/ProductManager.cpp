#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <set>
#include "ProductManager.h"
#include "Product.h"

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
    enum MenuOptions { DISPLAY_PRODUCT_LIST = 1, INPUT_PRODUCT, UPDATE_PRODUCT, DELETE_PRODUCT, DISPLAY_BY_CATEGORY, DELETE_CATEGORY, QUIT_PROGRAM };

    //clearConsole();
    cout << "                                              " << endl;
    cout << "=============================================" << endl;
    cout << "              Product Manager                " << endl;
    cout << "=============================================" << endl;
    cout << "  1. Display Product List                   " << endl;
    cout << "  2. Input Product                          " << endl;
    cout << "  3. Update Product                          " << endl;
    cout << "  4. Delete Product                         " << endl;
    cout << "  5. Display Products by Category           " << endl;
    cout << "  6. Delete Category                        " << endl;
    cout << "  7. Quit this Menu                         " << endl;
    cout << "=============================================" << endl;
    cout << " What do you want to do? ";

    int id;
    int menu;
    string categoryName;
    cin >> menu;
    cin.ignore();
    switch (menu) {
    case DISPLAY_PRODUCT_LIST:
        //clearConsole();
        displayItemsInfo();
        //cin.ignore();
        break;

    case INPUT_PRODUCT:
        //clearConsole();
        cout << "                                              " << endl;
        cout << "---------------------------------------------" << endl;
        cout << "                Input Product                " << endl;
        cout << "---------------------------------------------" << endl;
        inputItem();
        break;

    case UPDATE_PRODUCT:
        cout << "                                              " << endl;
        cout << "---------------------------------------------" << endl;
        cout << "                Update Product                " << endl;
        cout << "---------------------------------------------" << endl;
        displayItemsInfo();
        cout << "Enter product ID to update : ";
        cin >> id;
        cin.ignore();
        if (!contains(id)) {
            cout << "Product not found." << endl;
            break;
        }
        updateProduct(id);
        break;

    case DELETE_PRODUCT:
        //clearConsole();
        cout << "                                              " << endl;
        cout << "---------------------------------------------" << endl;
        cout << "                Delete Product               " << endl;
        cout << "---------------------------------------------" << endl;
        displayItemsInfo();
        cout << "Choose product id : ";
        cin >> id;
        if (remove(id)) {
            notify(id);
        }
        break;

    case DISPLAY_BY_CATEGORY:
        //clearConsole();
        cout << "                                              " << endl;
        cout << "---------------------------------------------" << endl;
        cout << "        Display Products by Category         " << endl;
        cout << "---------------------------------------------" << endl;
        displayCategoryList();
        {
            string categoryName;
            cout << "Enter category name: ";
            getline(cin, categoryName);
            displayProductsByCategory(categoryName);
        }
        break;

    case DELETE_CATEGORY:
        cout << "                                              " << endl;
        cout << "---------------------------------------------" << endl;
        cout << "               Delete Category               " << endl;
        cout << "---------------------------------------------" << endl;
        displayCategoryList();

        {
            string categoryName;
            cout << "   Choose category name to delete: ";
            getline(cin, categoryName);
            cout << "You entered: " << categoryName << endl;

            // 카테고리 존재 여부 확인
            bool categoryExists = false;
            for (const auto& it : mItemMap) {
                Product* product = it.second;
                if (product->getCategory().getName() == categoryName) {
                    categoryExists = true;
                    break;
                }
            }

            if (categoryExists) {
                CategoryDelete(categoryName);
            }
            else {
                cout << "Category '" << categoryName << "' does not exist." << endl;
                cout << "                                              " << endl;
            }
        }
        break;


    case QUIT_PROGRAM:
        return true;

    default:
        cout << "Invalid option. Please choose a number between " << DISPLAY_PRODUCT_LIST << " and " << QUIT_PROGRAM << "." << endl;
        break;
    }

    return false;
}

void ProductManager::displayItemsInfo() const
{
    cout <<  endl;
    cout << "Product list" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "   ID   |    Name       |   Price  | Category   " << endl;
    cout << "---------------------------------------------" << endl;

    for (const auto& it : mItemMap) {
        Product* product = it.second;
        cout << setw(5) << setfill('0') << right << product->getId() << " | "
            << setw(10) << setfill(' ') << right << product->getName() << " | "
            << setw(10) << setfill(' ') << right << product->getPrice().get() << " | "
            << setw(10) << setfill(' ') << right << product->getCategory().getName() << endl;
    }

    cout << "---------------------------------------------" << endl;
    cout << "Press Enter to return to the menu...";
    cout << endl;
}


void ProductManager::inputItem()
{
    string name;
    int priceInput;
    string categoryInput;

    cout << "Name: ";
    getline(cin, name);

    cout << "Price: ";
    cin >> priceInput;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(LLONG_MAX, '\n');
        logger.error("Failed to add product: Name=" + name + ", Error=Invalid price input.");
        cout << "Failed to create product. Please try again." << endl;
        return;
    }
    cin.ignore();

    cout << "Category: ";
    getline(cin, categoryInput);

    if (categoryInput.empty()) {
        categoryInput = "No Category";
    }

    try {
        Price price(priceInput);
        //Category category(categoryInput);
        Category* category = getOrCreateCategory(categoryInput);

        if (category == nullptr) {
            cout << "Product was not added." << endl;
            return;
        }

        Product newProduct(generateId(), name, price, *category);
        add(newProduct);
        category->addProduct(&newProduct);

        logger.info("Product added: Name=" + name + ", Price=" + to_string(priceInput) + ", Category=" + categoryInput);

    }
    catch (const invalid_argument& e) {
        logger.error("Failed to add product: Name=" + name + ", Error=" + string(e.what()));
    }
}

void ProductManager::updateProduct(unsigned int id)
{
    const Product& productToUpdate = getById(id);
    
    string newName;
    int newPrice;
    string priceInput;
    string newCategoryName;

    cout << "Enter new name : ";
    getline(cin, newName);
    if (newName.empty()) {
        newName = productToUpdate.getName(); 
    }

    cout << "Enter new price : ";
    getline(cin, priceInput); 
    if (!priceInput.empty()) {
        try {
            newPrice = stoi(priceInput);
        }
        catch (const invalid_argument& e) {
            cout << "Invalid price format. Keeping the current price." << endl;
            newPrice = productToUpdate.getPrice().get(); // 변환 실패 시 기존 가격 유지
        }
        catch (const out_of_range& e) {
            cout << "Price out of range. Keeping the current price." << endl;
            newPrice = productToUpdate.getPrice().get(); // 범위 초과 시 기존 가격 유지
        }
    }
    else {
        newPrice = productToUpdate.getPrice().get(); 
    }

    cout << "Enter new category : ";
    getline(cin, newCategoryName);
    if (newCategoryName.empty()) {
        newCategoryName = productToUpdate.getCategory().getName();  
    }
    Category* newCategory = getOrCreateCategory(newCategoryName);
    if (newCategory == nullptr) {
        cout << "Failed to update product to invalid category" << endl;
        return;
    }

    Product updatedProduct(id, newName, Price(newPrice), *newCategory);

    // BaseManager update 
    if (update(id, updatedProduct)) {
        logger.info("Product updated: ID=" + to_string(id) + ", Name=" + newName + ", Price=" + to_string(newPrice));
        cout << "Product updated successfully!" << endl;
    }
    else {
        cout << "Failed to update product." << endl;
    }

}

void ProductManager::notify(unsigned int id)
{
    for (const auto& it : observers)
    {
        it->update(id);
    }
}

void ProductManager::displayProductsByCategory(const string& categoryName)
{
    cout << "Products in category: " << categoryName << endl;
    bool found = false;
    for (const auto& it : mItemMap) {
        Product* product = it.second;
        if (product->getCategory().getName() == categoryName) {
            cout << product->getName() << endl;
            found = true;
        }
    }
    cout << "                                              " << endl;
    if (!found) {
        cout << "No products found in this category. " << endl;
        cout <<  endl;
    }
}

void ProductManager::displayCategoryList() const
{
    cout << "                                              " << endl;
    cout << "Category List:" << endl;

    set<string> categories;

    for (const auto& it : mItemMap) {
        Product* product = it.second;
        categories.insert(product->getCategory().getName());
    }

    for (const auto& category : categories) {
        cout << category << endl;
    }

    cout << "---------------------------------------------" << endl;
    cout << "Press Enter to return to the menu...";
    cin.ignore();
}


bool ProductManager::isCategoryExists(const string& categoryName) const
{
    return mCategoryMap.find(categoryName) != mCategoryMap.end();
}

void ProductManager::addCategory(const string& categoryName)
{
    Category* newCategory = new Category(categoryName);
    mCategoryMap[categoryName] = newCategory;
    cout << "Category '" << categoryName << "' has been added." << endl;
    cout << "                                              " << endl;
}

Category* ProductManager::getOrCreateCategory(const string& categoryName)
{
    if (isCategoryExists(categoryName)) {
        return mCategoryMap[categoryName];
    }
    else {
        cout << "Category '" << categoryName << "' does not exist. Do you want to add it? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();

        if (choice == 'y' || choice == 'Y') {
            addCategory(categoryName);
            return mCategoryMap[categoryName];
        }
        else {
            cout << "Add to No Category." << endl;
            return nullptr;
        }
    }
}

void ProductManager::CategoryDelete(const string& categoryName)
{
    // 카테고리와 연관된 상품이 있는지 확인
    bool hasProducts = false;
    vector<unsigned int> idsToDelete;

    for (const auto& it : mItemMap) {
        Product* product = it.second;
        if (product->getCategory().getName() == categoryName) {
            hasProducts = true;
            idsToDelete.push_back(product->getId());
        }
    }

    if (hasProducts) {
        cout << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Category '" << categoryName << "' has associated products." << endl;
        cout << "How would you like to handle the products in this category?" << endl;
        cout << "1. Delete all products in this category." << endl;
        cout << "2. Cancel and do nothing." << endl;
        cout << "Please choose an option (1/2): ";
        cout << "---------------------------------------------" << endl;

        char choice;
        cin >> choice;
        cin.ignore();

        if (choice == '1') {
            // 카테고리 내 모든 상품 삭제
            for (unsigned int id : idsToDelete) {
                remove(id);  // BaseManager의 remove 메소드 호출
            }
            
            cout << "All products in category '" << categoryName << "' have been deleted." << endl;
        }
        else if (choice == '2') {
            cout << "Operation cancelled. No changes were made." << endl;
        }
        else {
            cout << "Invalid choice. No changes were made." << endl;
        }
    }
    else {
        //상품이 없으면 카테고리 삭제
        cout << "No products are associated with category '" << categoryName << "'." << endl;

        auto categoryIt = mCategoryMap.find(categoryName);
        if (categoryIt != mCategoryMap.end()) {
            delete categoryIt->second;
            mCategoryMap.erase(categoryIt);
            cout << "Category '" << categoryName << "' has been deleted." << endl;
        }
        else {
            cout << "Category '" << categoryName << "' was not found in the category map." << endl;
        }
    }
}
