#ifndef __CLIENTMANAGER_H_
#define __CLIENTMANAGER_H_
#include<vector>
#include<map>
#include<string>
class Client;
using namespace std;
class ClientManager
{
public:
	ClientManager();
	void addClient(Client* adClient);
	void deleteClient();
	void inputClient();
	void updateClient();
	vector<string> parseCSV(istream& file, char delimiter);
	bool displayMenu();
	void displayInfo();
	~ClientManager();
private:
	map<int, Client*> clientList;
};
#endif