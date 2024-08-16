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
	vector<string> sellinf;
	ProductManager pm;
	Store s;
	map<int, Product*> productList = pm.getList();
	vector<int> sellId = s.getSellList();
	for (const auto& v : productList)
	{
		if (find(sellId.begin(), sellId.end(), v.first) != sellId.end())
		{
			vector<string> sellinfo;
			sellinfo.push_back(v.second->getName());
			sellinfo.push_back(to_string(v.second->getPrice()));
			sellinfo.push_back(v.second->getCategory());
			sellinfo.push_back(to_string(s.getInventory(v.first)));
			sellItems[v.first] = sellinfo;
		}
	}
}
StoreManager::~StoreManager()
{

}

void StoreManager::sell()
{

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