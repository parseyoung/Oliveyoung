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
    enum MenuOptions { DISPLAY_PRODUCT_LIST = 1, INPUT_PRODUCT, DELETE_PRODUCT, DISPLAY_BY_CATEGORY, QUIT_PROGRAM };

    //clearConsole();
    cout << "=============================================" << endl;
    cout << "              Product Manager                " << endl;
    cout << "=============================================" << endl;
    cout << "  1. Display Product List                   " << endl;
    cout << "  2. Input Product                          " << endl;
    cout << "  3. Delete Product                         " << endl;
    cout << "  4. Display Products by Category           " << endl;
    cout << "  5. Quit this Program                      " << endl;
    cout << "=============================================" << endl;
    cout << " What do you want to do? ";

    int id;
    int menu;
    cin >> menu;
    cin.ignore();
    switch(menu) {
        case DISPLAY_PRODUCT_LIST:
            //clearConsole();
            displayItemsInfo();
            //cin.ignore();
            break;

        case INPUT_PRODUCT:
            //clearConsole();
            cout << "---------------------------------------------" << endl;
            cout << "                Input Product                " << endl;
            cout << "---------------------------------------------" << endl;
            inputItem();
            break;

        case DELETE_PRODUCT:
            //clearConsole();
            cout << "---------------------------------------------" << endl;
            cout << "                Delete Product               " << endl;
            cout << "---------------------------------------------" << endl;
            displayItemsInfo();
            cout << "   Choose product id : ";
            cin >> id;
            if(remove(id)){
                notify(id);
            }
            break;

        case DISPLAY_BY_CATEGORY:
            //clearConsole();
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
    cout << "Product list" << endl;
    cout << "=============================================" << endl;
    cout << "   ID   |    Name       |   Price  | Category   " << endl;
    cout << "=============================================" << endl;

    for (const auto& it : mItemMap) {
        Product* product = it.second;
        cout << setw(5) << setfill('0') << right << product->getId() << " | "
            << setw(10) << setfill(' ') << right << product->getName() << " | "
            << setw(10) << setfill(' ') << right << product->getPrice().get() << " | "
            << setw(10) << setfill(' ') << right << product->getCategory().getName() << endl;
    }

    cout << "=============================================" << endl;
    cout << "Press Enter to return to the menu...";
    cin.ignore(); 
    cin.get();    
}


void ProductManager::inputItem()
{
    string name;
    int priceInput;
    string categoryInput;
    cout << "Name : "; cin >> name;
    cout << "Price : "; cin >> priceInput;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(LLONG_MAX, '\n');
        logger.error("Failed to add product: Name=" + name + ", Error=Invalid price input.");
        cout << "Failed to create product. Please try again." << endl;
        return;
    }
    cout << "Category : "; cin >> categoryInput;

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
        cout << "No products found in this category. " << endl;
    }
}

void ProductManager::displayCategoryList() const
{
    cout << "Category List:" << endl;

    set<string> categories; 

    for (const auto& it : mItemMap) {
        Product* product = it.second;
        categories.insert(product->getCategory().getName());
    }

    for (const auto& category : categories) {
        cout << category << endl;
    }

    cout << "=============================================" << endl;
    cout << "Press Enter to return to the menu...";
    cin.ignore(); 
}
