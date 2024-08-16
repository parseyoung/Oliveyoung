#include"clientmanager.h"
#include"productmanager.h"
#include"StoreManager.h"
#include"Product.h"
#include"Store.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>
using namespace std;

StoreManager::StoreManager()
{
	readFile();
	todayRecord.clear();
	record();//전날 내용 지움
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
void StoreManager::showTodayRecord()//csv파일 읽어오기
{
	ifstream file;
	file.open("today record.txt");
	cout << endl << "User Name     |     Product       |     Price     |   Category" << endl;
	if (!file.fail()) {
		while (!file.eof()) {
			vector <int > state;
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = atoi(row[0].c_str());
				string name = row[1];
				int price = atoi(row[2].c_str());
				string category = row[3];
				cout << setw(5) << setfill('0') << right << id << " | " << left;
				cout << setw(14) << name << " | ";
				cout << setw(14) << price << " | ";
				cout << category << endl;
			}
		}
	}

	file.close();
}
void StoreManager::record()
{
	ofstream file;
	ProductManager pm;
	file.open("today record.txt");

	if (!file.fail())
	{
		for (const auto& v : todayRecord) {
			string name = v.second[0];
			string price = v.second[1];
			string category = v.second[2];
			file << v.first << ", " << name << "," << price << ",";
			file << category << endl;

		}
	}

	file.close();
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
				vector<string> info;
				info.push_back(v.second[0]);
				info.push_back(v.second[1]);
				info.push_back(v.second[2]);
				todayRecord.insert({ v.first ,info });
				record();//오늘기록파일에 구매자 아이디, 상품이름, 가격, 카테고리 저장
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
			showTodayRecord();
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
vector<string> StoreManager::parseCSV(istream& file, char delimiter)
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