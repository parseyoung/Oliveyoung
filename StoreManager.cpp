#include"clientmanager.h"
#include"productmanager.h"
#include"StoreManager.h"
#include"Product.h"
#include"Store.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>
using namespace std;

StoreManager::StoreManager()
{
	readFile();
}
StoreManager::~StoreManager()
{

}
void StoreManager::readFile()
{
	ProductManager pm;
	Store s;
	map<int, Product*> productList = pm.getList();
	vector<int> sellId = s.getSellList();
	sellItems.clear();
	for (const auto& v : productList)
	{
		if (find(sellId.begin(), sellId.end(), v.first) != sellId.end())
		{
			vector<string> sellinfo;
			sellinfo.push_back(v.second->getName());
			sellinfo.push_back(to_string(v.second->getPrice()));
			sellinfo.push_back(v.second->getCategory());
			sellinfo.push_back(to_string(s.getInventory(v.first)));
			sellItems.insert({ v.first,sellinfo });
		}
	}
}
void StoreManager::inputUserId()
{
	int userId;
	ClientManager cm;
	cout << "Enter Id >> ";
	cin >> userId;
	cin.ignore();
	if (cm.isExist(userId))
	{
		sell();
	}
	else {
		cout << "first visit custumer! please sign up" << endl;
	}
}
//bool changeFlag()
//{
//	return true;
//}
void StoreManager::sell()//sell 에서 물건 안찾아짐//
{
	string sellName;
	ProductManager pm;
	Store s;
	int sellPrice;
	cout << "what do you want to buy?>> ";
	getline(cin, sellName);
	string isPay;
	for (const auto& v : sellItems)
	{
		cout << v.second[0] << endl;
		if (v.second[0] == sellName)
		{

			sellPrice = pm.getList()[v.first]->getPrice();
			cout << "Selected " << sellName << "cost : " << sellPrice << endl;
			cout << "Pay Y/N>> ";
			getline(cin, isPay);
			if (isPay == "y" || isPay == "Y")
			{
				cout << sellPrice << "has been paid" << endl;
				sellItems[v.first].at(3) = to_string(stoi(sellItems[v.first].at(3)) - 1);
				s.updateInventory(v.first);
				break;
			}
			else
			{
				cout << "Pay is Canceled" << endl;
				break;
			}
		}
		else {
			continue;
		}
		cout << "Can't find product" << endl;
	}
}
bool StoreManager::displayMenu()
{
	int quit = 0;
	readFile();
	while (quit != 1) {
		int ch;
		//cout << "\033[2J\033[1;1H";
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "              Store Manager                  " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "  1. Display Sell List                       " << endl;
		cout << "  2. Sell                                    " << endl;
		cout << "  3. Show Record                             " << endl;
		cout << "  4. Quit this Program                       " << endl;
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
			displayInfo();
			inputUserId();
			break;
		case 3:
			displayInfo();
			break;
		case 4:
			quit = 1;
			break;
		}
	}
	return true;
}
void StoreManager::displayInfo()
{
	cout << endl << "Name     |     Price       |     Category     |   Inventory" << endl;
	for (const auto& v : sellItems) {

		cout << setw(14) << setfill(' ') << v.second[0] << " | ";
		cout << setw(14) << v.second[1] << " | ";
		cout << setw(14) << setfill(' ') << v.second[2] << " | ";
		cout << v.second[3] << endl;
	}
}