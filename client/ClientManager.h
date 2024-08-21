#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <vector>
#include <map>

#include "Client.h"
#include "../database/Constants.h"
#include "../Validation/BaseEntity.h"

using namespace std;

// 저장소
namespace ClientManagerConstants {
    const string RESOURCE = DIR_DATABASE + "client_list.csv";
}

class ClientManager : public BaseEntity<Client> 
{
public:
    ClientManager();
    ~ClientManager();
    ClientManager(const ClientManager& other);
    
    // 데이터 관리 
    bool add(const Client& client) override;
    bool remove(const unsigned int id) override;
    const Client* getByIdOrNull(const unsigned int id) const;


    // 저장소 관리
    void load();

    // View 관리
    const bool displayMenu();
    void displayItemsInfo() const;
    void inputItem();

private:
    
    unsigned int generateId() const;  // ID 생성 메소드
    vector<string> parseCSV(istream& stream, char delimiter);
    void appendToFile(const Client& client) const override;
    void removeFromFile(const unsigned int id) const override;

    map<unsigned int, Client*> mClientMap;
};

#endif // CLIENT_MANAGER_H