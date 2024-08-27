#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "../include/BaseManager.h"
#include "Client.h"
#include "../database/Constants.h"
#include "../logger/Logger.h"

using namespace std;

class ClientManager : public BaseManager<Client>
{
public:
    ClientManager();

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();

private:
    static Logger logger;
};

#endif // CLIENT_MANAGER_H