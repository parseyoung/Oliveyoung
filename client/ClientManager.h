#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "Client.h"
#include "../Manager.h"
#include "../database/Constants.h"

using namespace std;

// 저장소
namespace ClientManagerConstants {
    const string RESOURCE = DIR_DATABASE + "client_list.csv";
}

class ClientManager : Manager
{
public:
    ClientManager();
    ~ClientManager();
    ClientManager(const ClientManager& other);
    
    // 데이터 관리 
    const bool add(const Client& client);
    const bool remove(const unsigned int id);
    const Client* getByIdOrNull(const unsigned int id) const;

    // 저장소 관리
    void load();

    // View 관리
    const bool displayMenu();
    void displayInfo() const;
    void inputItem();
private:
    void appendToFile(const Client& client) const;
    void removeFromFile(const unsigned int id) const;
    const unsigned int generateId() const;
    map<unsigned int, Client*> mClientMap;
};

#endif // CLIENT_MANAGER_H