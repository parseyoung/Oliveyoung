#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>
#include"productmanager.h"
#include"product.h"

using namespace std;

ProductManager::ProductManager()
{
	readFile();
	makeIdList();
}
ProductManager::~ProductManager()
{
	writeFile();
	for (int i = 0; i < productList.size(); i++)//!!!!!!!!!!!!!!!!!
	{
		delete productList[i];
	}

}
void ProductManager::readFile()
{
	ifstream file;
	file.open("productInfo.csv");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = atoi(row[0].c_str());
				int price = atoi(row[2].c_str());
				Product* c = new Product(id, row[1], price, row[3]);
				productList.insert({ id, c });
			}
		}
	}
	file.close();
}
map<int, Product*> ProductManager::getList()
{
	return productList;
}
void ProductManager::writeFile()
{
	ofstream file;
	file.open("productInfo.csv");
	if (!file.fail())
	{
		for (const auto& v : productList) {
			Product* c = v.second;
			file << c->getId() << ", " << c->getName() << ",";
			file << c->getPrice() << ", ";
			file << c->getCategory() << endl;
		}
	}
	file.close();

}

void ProductManager::inputProduct()
{
	Product* newProduct = new Product;
	string name, category, qsave;
	int price;
	cout << "Enter the information of the product you want to add" << endl;
	cout << "Name : ";
	getline(cin, name);
	newProduct->setName(name);
	cout << "Price : ";
	cin >> price;
	cin.ignore();
	newProduct->setPrice(price);
	cout << "Category : ";
	getline(cin, category);
	newProduct->setCategory(category);
	cout << "SAVE : S  CANCEL : C >> ";
	getline(cin, qsave);
	if (qsave == "S" || qsave == "s")
	{
		if (productList.size() == 0)
		{
			newProduct->setId(1);
			addProduct(newProduct);
		}
		else
		{
			auto cur_id = --productList.end();
			int id = cur_id->first;

			newProduct->setId(++id);
			addProduct(newProduct);

		}

	}
	else
	{
		cout << "The entered information has been deleted\n";
	}

}
void ProductManager::addProduct(Product* adProduct)
{
	productList.insert({ adProduct->getId(), adProduct });
	writeFile();
}
void ProductManager::deleteProduct()
{
	int id;
	cout << "Enter ID to delete >> ";
	cin >> id;
	cin.ignore();
	auto itre = productList.find(id);
	if (itre != productList.end())
	{
		delete productList[id];
		productList.erase(id);
	}
	writeFile();


}
void ProductManager::updateProduct()
{
	int id;
	cout << "Enter ID to modify >> ";
	cin >> id;
	cin.ignore();
	Product* c = productList[id];
	cout << setw(6) << setfill('0') << right << c->getId() << " | " << left;
	cout << setw(14) << setfill(' ') << c->getName() << " | ";
	cout << setw(14) << c->getPrice() << " | ";
	cout << c->getCategory() << endl;
	cout << "1. name                  " << endl;
	cout << "2. price                 " << endl;
	cout << "3. category              " << endl;
	cout << "Select thing to modify>> ";
	int select;
	cin >> select;
	cin.ignore();
	string newName;
	int newPrice;
	string newCategory;
	switch (select)
	{
	case 1:
		cout << "Enter new name >> ";
		getline(cin, newName);
		c->setName(newName);
		writeFile();
		break;
	case 2:
		cout << "Enter new Price >> ";
		cin >> newPrice;
		cin.ignore();
		c->setPrice(newPrice);
		writeFile();
		break;
	case 3:
		cout << "Enter Category >> ";
		getline(cin, newCategory);
		c->setCategory(newCategory);
		writeFile();
		break;
	default:
		writeFile();
		break;
	}
}
vector<string> ProductManager::parseCSV(istream& file, char delimiter)
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
void ProductManager::displayInfo()
{
	cout << endl << "ID     |     Name     |     Price      |   Category" << endl;
	for (const auto& v : productList) {

		Product* c = v.second;
		cout << setw(6) << setfill('0') << right << c->getId() << " | " << left;
		cout << setw(14) << setfill(' ') << c->getName() << " | ";
		cout << setw(14) << c->getPrice() << " | ";
		cout << c->getCategory() << endl;
	}
}
bool ProductManager::isExist(int id)
{
	if (productList.find(id) != productList.end()) {
		return true;
	}
	else {
		return false;
	}
}
void ProductManager::makeIdList()
{
	for (const auto& v : productList)
	{
		idList.push_back(v.first);
	}
}
vector <int> ProductManager::getIdList()
{
	return idList;
}
bool ProductManager::displayMenu()
{
	int quit = 0;
	while (quit != 1) {
		int ch;
		//cout << "\033[2J\033[1;1H";
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "              Product Manager                 " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "  1. Display Product List                     " << endl;
		cout << "  2. input Product                            " << endl;
		cout << "  3. Delete Product                           " << endl;
		cout << "  4. Modify Product                           " << endl;
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
			inputProduct();
			break;
		case 3:
			displayInfo();
			deleteProduct();
			break;
		case 4:
			displayInfo();
			//cout << "   Choose Key : ";
			//cin >> key;
			updateProduct();
			break;
		case 5:
			quit = 1;
			break;
		}

	}
	return true;
}