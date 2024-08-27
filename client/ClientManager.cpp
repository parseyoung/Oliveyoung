#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>

#include "ClientManager.h"
#include "Client.h"
#include "Name.h"
#include "PhoneNumber.h"
#include "Point.h"


using namespace std;

// 저장소
namespace ClientManagerConstants {
    const string RESOURCE = DIR_DATABASE + "client_list.csv";
}

Logger ClientManager::logger("ClientManager");

ClientManager::ClientManager() : BaseManager<Client>(ClientManagerConstants::RESOURCE) 
{
}

void clearConsole() {
    system("clear");
    // cout << "\033[2J\033[1;1H";
}

// View 관리
const bool ClientManager::displayMenu() 
{
    enum MenuOptions { DISPLAY_CLIENT_LIST = 1, INPUT_CLIENT, DELETE_CLIENT, QUIT_PROGRAM };

    // clearConsole();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Client Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Client List                     " << endl;
    cout << "  2. input Client                            " << endl;
    cout << "  3. Delete Client                           " << endl;
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
            cout << "Input Client (name)" << endl;
            cout << setw(45) << setfill('-') << "\n" << endl;
            inputItem();

            break;
        case DELETE_CLIENT:
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Delete Client" << endl;;
            cout << setw(45) << setfill('-') << "\n" << endl;

            displayItemsInfo();
            cout << "   Choose client id : ";

            cin >> id;
            remove(id);

            break;
        case QUIT_PROGRAM:
            return true;

        default:
            cout << DISPLAY_CLIENT_LIST << "와 " << QUIT_PROGRAM << " 사이의 값을 입력하세요." << endl;
            break;
    }

    return false;
}



void ClientManager::displayItemsInfo() const
{
    cout << "Client list" << endl;
    cout << endl << "  ID  |     Name     " << endl;
    for (const auto& it : mItemMap) {
        Client* client = it.second;
        cout << setw(5) << setfill('0') << right << client->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << client->getName().get() << " | ";
        cout << setw(13) << setfill(' ') << client->getPhoneNumber().getFullNumber() << " | ";
        cout << setw(10) << setfill(' ') << client->getPoint().get() << endl;
    }

    cout << endl;
    cout << "return to menu: enter any key" << endl;
}

void ClientManager::inputItem()
{
    string nameInput;
    string phoneNumberInput;
    int pointInput;
    cout << "name : "; cin >> nameInput;
    cout << "phone number : "; cin >> phoneNumberInput;
    cout << "initial point : "; cin >> pointInput;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(LLONG_MAX, '\n');
        logger.error("Failed to add client: Name=" + nameInput + " Phone number: " + phoneNumberInput + ", Error=Invalid initial point input.");
        cout << "Client 생성에 실패했습니다. 다시 시도하세요." << endl;
        return;
    }

    try {
        Name name(nameInput);
        PhoneNumber phoneNumber(phoneNumberInput);
        Point point(pointInput);

        add(Client(generateId(), name, phoneNumber, point));
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        cout << "Client 생성에 실패했습니다. 다시 시도하세요." << endl;
    }
}
