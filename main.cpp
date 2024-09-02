#include "store/StoreManager.h"
#include "store/Store.h"
#include "client/ClientManager.h"
#include "product/ProductManager.h"

#include <iostream>

using namespace std;
void displayMainMenu() {
    cout << "                                               " << endl;
    cout << "***********************************************" << endl;
    cout << "*                                             *" << endl;
    cout << "*  W E L C O M E   T O   O L I V E Y O U N G  *" << endl;
    cout << "*                                             *" << endl;
    cout << "***********************************************" << endl;
    cout << "*                                             *" << endl;
    cout << "*   1. Store Management                       *" << endl;
    cout << "*   2. Client Management                      *" << endl;
    cout << "*   3. Product Management                     *" << endl;
    cout << "*   4. Quit                                   *" << endl;
    cout << "*                                             *" << endl;
    cout << "***********************************************" << endl;
    cout << "Please select an option: ";
}

int main(void)
{   
    //system("chcp 65001");
    ClientManager clientManager = ClientManager();
    ProductManager productManager = ProductManager();
    Store store = Store("OliveYoung");
    StoreManager storeManager = StoreManager(store, productManager, clientManager);
    cout << "set up done" << endl;
    cout<< "Welcome: " + store.getName() << endl;

    
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