#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H


#include "../include/BaseManager.h"
#include "../include/ViewManager.h"
#include "Client.h"
#include "../database/Constants.h"

using namespace std;

class ClientManager : public BaseManager<Client>, public ViewManager
{
public:
    ClientManager();

    // View 관리
    const bool displayMenu() override;
    void displayItemsInfo() const override;
    void inputItem() override;

    void notify(unsigned int id);
private:
};

#endif // CLIENT_MANAGER_H
