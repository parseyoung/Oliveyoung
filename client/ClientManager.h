#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "../include/BaseManager.h"
#include "Client.h"
#include "../database/Constants.h"

using namespace std;

// 저장소
namespace ClientManagerConstants {
    const string RESOURCE = DIR_DATABASE + "client_list.csv";
}

class ClientManager : public BaseManager<Client>
{
public:
    ClientManager() : BaseManager<Client>(ClientManagerConstants::RESOURCE) {};

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();

private:
};

#endif // CLIENT_MANAGER_H