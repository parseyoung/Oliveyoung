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
    enum MenuOptions { DISPLAY_CLIENT_LIST = 1, INPUT_CLIENT, DELETE_CLIENT, DISPLAY_BY_CATEGORY, QUIT_PROGRAM };

    // clearConsole();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Display Products by Category             " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    
    int id;
    int menu;
    cin >> menu;
    cin.ignore();
    switch(menu) {
        case DISPLAY_CLIENT_LIST: 
            // clearConsole();

            displayItemsInfo();
            cin.ignore();
           // getchar();

            break;
        case INPUT_CLIENT:
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Input Product (name)" << endl;
            cout << setw(45) << setfill('-') << "\n" << endl;
            inputItem();
            break;
        case DELETE_CLIENT:
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Delete Product" << endl;;
            cout << setw(45) << setfill('-') << "\n" << endl;

            displayItemsInfo();
            cout << "   Choose product id : ";

            cin >> id;
            if(remove(id)){
                notify(id);
            }
            break;
        case DISPLAY_BY_CATEGORY:
            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Display Products by Category" << endl;
            cout << setw(45) << setfill('-') << "\n" << endl;
            // 카테고리 목록을 먼저 출력
            displayCategoryList();
            {
                string categoryName;
                cout << "Enter category name: ";
                getline(cin, categoryName); // Ensure category name is properly read
                displayProductsByCategory(categoryName);
            }
            break;

        case QUIT_PROGRAM:
            return true;

        default:
            cout << DISPLAY_CLIENT_LIST << "와 " << QUIT_PROGRAM << " 사이의 값을 입력하세요." << endl;
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(LLONG_MAX, '\n');
        logger.error("Failed to add product: Name=" + name + ", Error=Invalid price input.");
        return;
    }
    cout << "category : "; cin >> categoryInput;

    try {
        Price price(priceInput);
        Category category(categoryInput);

        Product newProduct(generateId(), name, price, category);
        add(newProduct);
        
        logger.info("Product added: Name=" + name + ", Price=" + to_string(priceInput) + ", Category=" + categoryInput);

    } catch (const invalid_argument& e) {
        logger.error("Failed to add product: Name=" + name + ", Error=" + string(e.what()));
    }
    catch (const std::out_of_range& e) {
        cout << "Error: " << e.what() << endl;
        logger.error("Failed to add product: Name=" + name + ", Error=" + string(e.what()));
    }
}

void ProductManager::notify(unsigned int id)
{
    for(const auto & it:observers)
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
            //cout << product->toString() << endl;
            cout << product->getName() << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "해당 카테고리의 상품을 찾을 수 없습니다. " << endl;
    }
}

void ProductManager::displayCategoryList() const
{
    cout << "카테고리 목록:" << endl;

    set<string> categories; // 중복을 제거하기 위해 set 사용

    // 모든 제품을 순회하면서 카테고리 수집
    for (const auto& it : mItemMap) {
        Product* product = it.second;
        categories.insert(product->getCategory().getName());
    }

    // 카테고리 목록 출력
    for (const auto& category : categories) {
        cout << category << endl;
    }

    cout << endl;
    cout << "Return to menu: enter any key" << endl;
    cin.ignore(); // 사용자가 아무 키나 누를 때까지 대기
}
