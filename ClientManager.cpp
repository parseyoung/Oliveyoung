#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>
#include"clientmanager.h"
#include"client.h"

using namespace std;

ClientManager::ClientManager()
{
	readFile();
}
ClientManager::~ClientManager()
{

	for (int i = 0; i < clientList.size(); i++)
	{
		delete clientList[i];
	}
}
void ClientManager::readFile()
{
	ifstream file;
	file.open("clientInfo.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = atoi(row[0].c_str());
				Client* c = new Client(id, row[1], row[2], row[3]);
				clientList.insert({ id, c });
			}
		}
	}

	file.close();
}
void ClientManager::writeFile()
{
	ofstream file;
	file.open("clientInfo.txt");
	if (!file.fail())
	{
		for (const auto& v : clientList) {
			Client* c = v.second;
			file << c->getId() << ", " << c->getName() << ",";
			file << c->getPhoneNum() << ", ";
			file << c->getAddress() << endl;
		}
	}
	file.close();
}

bool ClientManager::isExist(int id)
{
	if (clientList.find(id) != clientList.end()) {
		return true;
	}
	else {
		return false;
	}
}
vector<int>ClientManager::getclientIdList()
{
	readFile();
	vector<int>clientIdList;
	for (const auto& v : clientList)
	{
		clientIdList.push_back(v.first);
	}
	return clientIdList;
}
void ClientManager::inputClient()
{
	Client* new_client = new(Client);
	string name, address, phoneNum, qsave;
	cout << "Enter the information of the customer you want to add" << endl;
	cout << "Name : ";
	getline(cin, name);
	new_client->setName(name);
	cout << "Phone Number : ";
	getline(cin, phoneNum);
	new_client->setPhoneNum(phoneNum);
	cout << "Adress : ";
	getline(cin, address);
	new_client->setAddress(address);
	cout << "SAVE : S  CANCEL : C >> ";
	getline(cin, qsave);
	if (qsave == "S" || qsave == "s")
	{
		if (clientList.size() == 0)
		{
			new_client->setId(1);
			addClient(new_client);
			writeFile();
		}
		else
		{
			auto cur_id = --clientList.end();
			int id = cur_id->first;

			new_client->setId(++id);
			addClient(new_client);
			writeFile();
		}

	}
	else
	{
		cout << "The entered information has been deleted\n";
	}

}
void ClientManager::addClient(Client* adClient)
{
	clientList.insert({ adClient->getId(), adClient });
}

void ClientManager::deleteClient()
{
	int id;
	cout << "Enter ID to delete >> ";
	cin >> id;
	cin.ignore();
	auto itre = clientList.find(id);
	if (itre != clientList.end())
	{
		delete clientList[id];
		clientList.erase(id);
	}
	writeFile();


}
void ClientManager::updateClient()
{
	int id;
	cout << "Enter ID to modify >> ";
	cin >> id;
	cin.ignore();
	Client* c = clientList[id];
	cout << setw(5) << setfill('0') << right << c->getId() << " | " << left;
	cout << setw(12) << setfill(' ') << c->getName() << " | ";
	cout << setw(12) << c->getPhoneNum() << " | ";
	cout << c->getAddress() << endl;
	cout << "1. name                  " << endl;
	cout << "2. phone number          " << endl;
	cout << "3. address               " << endl;
	cout << "Select thing to modify>> ";
	int select;
	cin >> select;
	cin.ignore();
	string new_name;
	string new_phone;
	string new_address;
	switch (select)
	{
	case 1:
		cout << "Enter new name >> ";
		getline(cin, new_name);
		c->setName(new_name);
		writeFile();
		break;
	case 2:
		cout << "Enter new phone number >> ";
		getline(cin, new_phone);
		c->setPhoneNum(new_phone);
		writeFile();
		break;
	case 3:
		cout << "Enter new address >> ";
		getline(cin, new_address);
		c->setAddress(new_address);
		writeFile();
		break;
	default:
		break;
	}
}
vector<string> ClientManager::parseCSV(istream& file, char delimiter)
{
	vector<string> row;
	stringstream ss;

	string t = " \n\r\t";

	while (!file.eof()) {
		char c = file.get();
		if (c == delimiter || c == '\r' || c == '\n') {
			if (file.peek() == '\n') file.get();
			string s = ss.str();
			s.erase(0, s.find_first_not_of(t));
			s.erase(s.find_last_not_of(t) + 1);
			row.push_back(s);
			ss.str("");
			if (c != delimiter) break;
		}
		else {
			ss << c;
		}
	}


	return row;
}
void ClientManager::displayInfo()
{
	cout << endl << "  ID  |     Name     | Phone Number |       Address" << endl;
	for (const auto& v : clientList) {
		Client* c = v.second;
		cout << setw(5) << setfill('0') << right << c->getId() << " | " << left;
		cout << setw(12) << setfill(' ') << c->getName() << " | ";
		cout << setw(12) << c->getPhoneNum() << " | ";
		cout << c->getAddress() << endl;
	}
}

bool ClientManager::displayMenu()
{
	int quit = 0;
	while (quit != 1) {
		int ch;
		//cout << "\033[2J\033[1;1H";
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "              Client Manager                 " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "  1. Display Client List                     " << endl;
		cout << "  2. input Client                            " << endl;
		cout << "  3. Delete Client                           " << endl;
		cout << "  4. Modify Client                           " << endl;
		cout << "  5. Quit this Program                       " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << " What do you wanna do? ";
		cin >> ch;
		cin.ignore();
		switch (ch) {
		case 1: default:
			displayInfo();
			//cin.ignore();
			//getchar();
			break;
		case 2:
			inputClient();
			break;
		case 3:
			displayInfo();
			deleteClient();
			break;
		case 4:
			displayInfo();
			//cout << "   Choose Key : ";
			//cin >> key;
			updateClient();
			break;
		case 5:
			quit = 1;
			break;
		}

	}
	return true;
}