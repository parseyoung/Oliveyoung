#include "store/StoreManager.h"
#include "store/Store.h"
#include "client/ClientManager.h"
#include "product/ProductManager.h"
#include "product/CategoryManager.h"

#include <iostream>
using namespace std;

void displayMainMenu() {
    cout << "=============================================" << endl;
    cout << "          Welcome to Store Management        " << endl;
    cout << "=============================================" << endl;
    cout << "  1. Store Management                        " << endl;
    cout << "  2. Client Management                       " << endl;
    cout << "  3. Product Management                      " << endl;
    cout << "  4. Quit                                    " << endl;
    cout << "=============================================" << endl;
    cout << " Please select an option: ";
}

int main(void)
{   

    CategoryManager categoryManager; // Assuming a CategoryManager is required
    ProductManager productManager(categoryManager); // Initialize with a CategoryManager
    ClientManager clientManager; // Assuming a default constructor is okay
    Store store("OliveYoung");
    StoreManager storeManager(store, productManager, clientManager);

    cout << "Setup done" << endl;
    cout << "Welcome: " << store.getName() << endl;

    
    bool running = true;

    while (running) {
        displayMainMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                storeManager.displayMenu();
                break;

            case 2:
                clientManager.displayMenu();
                break;

            case 3:
                productManager.displayMenu();
                break;

            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                running = false;
                break;

            default:
                cout << "Invalid option. Please select a valid option." << endl;
                break;
        }
    }

    return 0;
}