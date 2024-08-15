#include"clientmanager.h"
#include"productmanager.h"
#include"StoreManager.h"
#include"Product.h"
#include"Store.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<map>
using namespace std;

StoreManager::StoreManager()
{
	Store s;
	ProductManager pm;
	vector<int> sellId;
	map<int, Product*> productList;
	vector<int> pi;//가격 재고
	vector<string> nc;//이름 카테고리
	sellId = s.getSellList();
	for (int i = 0; i < sellId.size(); i++)
	{
		int id = sellId[i];
		if (pm.isExist(sellId[i]))
		{
			pi.push_back(productList[id]->getPrice());
			pi.push_back(s.getInventory(id));
			sellItems.insert({ id,{productList[id]->getName(),pi} });
		}
		else {
			cout << "produuct number " << id << "is not exist." << endl;
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
	cout << endl << "Name     |     Price       |     Category     |   " << endl;
	for (const auto& v : sellItems) {

		cout << setw(6) << setfill('0') << right << c->getId() << " | " << left;
		cout << setw(14) << setfill(' ') << c->getName() << " | ";
		cout << setw(14) << c->getPrice() << " | ";
		cout << c->getCategory() << endl;
	}
}