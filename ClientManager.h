#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "Client.h"
#include <vector>
#include <map>
class ClientManager
{
public:
	ClientManager();
	~ClientManager();
	
	void addClient(const string& name, const string phone);
	void deleteClient(int id);
	void displayClient();
	bool displayMenu();
	Client* searchClient(int id);

private:
	map<int, Client*> mClientMap; 
	int makeId();
	vector<string> parseCSV(istream& file, char delimiter);

	void loadClientsFromFile();
	void saveClientsToFile();


};

#endif // CLIENTMANAGER_H
