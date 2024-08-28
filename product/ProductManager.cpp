#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>

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
    enum MenuOptions { DISPLAY_CLIENT_LIST = 1, INPUT_CLIENT, DELETE_CLIENT, QUIT_PROGRAM };

    // clearConsole();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    
    int id;
    int menu;
    cin >> menu;
    switch(menu) {
        case DISPLAY_CLIENT_LIST: 
            // clearConsole();

            displayItemsInfo();
            cin.ignore();
            getchar();

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
        cout << setw(12) << setfill(' ') << product->getCategory().get() << endl;
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
        add(Product(generateId(), name, price, category));
        
        logger.info("Product added: Name=" + name + ", Price=" + to_string(priceInput) + ", Category=" + categoryInput);

    } catch (const invalid_argument& e) {
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

