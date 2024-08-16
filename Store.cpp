#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>
#include"Store.h"
#include"productmanager.h"
using namespace std;

// �ڷ� ����� ������Ʈ �ȵǴ� ���� -> �ڷ� ����� ���� ����
//productmanager���� ���� ��ǰ �������Ͽ��� ����� �ϱ�-> �Ҹ��ڿ��� ��ǰ����Ʈ�� �ִ� ���̵��� ������ ���Ͽ� ����
// =>���α׷� ������ �ٽ� ����� ����������
// ���α׷� ������ ��ǰ ���� �� ��� -> ���������� ���Ͽ� �������� ���� �ᵵ ������ ������ ���÷��̳� ���� ������;;;;;
//id�� ���� �ǳ����� �ϳ����� ������ ����-> ��ǰlist���� �ǳ����� ������ �Է��ϸ� ����Ͱ� ���� ��ȣ�� id���� -> ���� �Է� �Ұ� ������ ����!

Store::Store()
{
	readFile();

}

Store::~Store()
{
	writeFile();
}
void Store::readFile()//csv���� �о����
{
	stateProduct.clear();
	ifstream file;
	file.open("productState.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector <int > state;
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				int id = atoi(row[0].c_str());
				int inventory = atoi(row[1].c_str());
				int isSell = atoi(row[2].c_str());
				state.push_back(inventory);
				state.push_back(isSell);
				stateProduct.insert({ id,state });
			}
		}
	}

	file.close();
}
void Store::writeFile()//csv���� ���� productList�� �����ϴ� id�� �ش��ϴ� ������ �Է�
{
	ofstream file;
	ProductManager pm;
	file.open("productState.txt");
	if (!file.fail())
	{
		for (const auto& v : stateProduct) { //��ǰ�� ���̵� ���δ�Ʈ����Ʈ�� �����ϴ��� Ȯ�� �� ������ ����
			if (pm.isExist(v.first)) {
				int id = v.first;
				int inventory = v.second[0];
				int isSell = v.second[1];
				file << id << ", " << inventory << ",";
				file << isSell << endl;
			}
			else {
				cout << "notice* " << "Product number " << v.first << " had been deleted from the product list and the product information will be deleted." << endl;
			}
		}
	}

	file.close();
}
void Store::addState() // ���� �߰��ϱ� ����: ���, �Ǹſ��� => ��ǰList�� �ִ� id�� ���°� �Էµ��� ���� �͸� �Է°���
{
	ProductManager pm;
	vector <int> pId = pm.getIdList();
	int quit = 0;
	for (int i = 0; i < pId.size(); i++)
	{
		if (stateProduct.find(pId[i]) == stateProduct.end()) {
			char isMore;
			int id, inventory, isSell;
			cout << "It is necessary to add the status of product number " << pId[i] << endl;
			cout << "Would you like to add the status of product number " << pId[i] << " Y/N>> ";
			cin >> isMore;
			cin.ignore();
			if (isMore == 'y' || isMore == 'Y')
			{
				vector <int>  newInfo;
				id = pId[i];

				cout << "Enter Inventory to add>> ";
				cin >> inventory;
				cin.ignore();
				newInfo.push_back(inventory);

				cout << "Enter isSell value to add : YES = 1, NO = 0 >> ";
				cin >> isSell;
				newInfo.push_back(isSell);
				cin.ignore();

				stateProduct.insert({ id,newInfo });
				writeFile();
			}
		}
		else {
			continue;
		}
	}
	cout << "There are no products that require adding status." << endl;
}
void Store::updateStatet()//���� ��ġ�� ���� �Ǹſ��� ��������
{
	int id;
	cout << "Enter ID to modify >> ";
	cin >> id;
	cin.ignore();
	cout << setw(5) << setfill('0') << right << id << " | " << left;
	cout << setw(12) << setfill(' ') << stateProduct[id][0] << " | ";
	cout << setw(12) << stateProduct[id][1] << endl;
	cout << "1. inventrory                  " << endl;
	cout << "2. Is selling          " << endl;
	cout << "Select thing to modify>> ";
	int select;
	cin >> select;
	cin.ignore();
	int inventory;
	int isSell;
	switch (select)
	{
	case 1:
		cout << "Enter new inventroy >> ";
		cin >> inventory;
		cin.ignore();
		stateProduct[id][0] = inventory;
		writeFile();
		break;
	case 2:
		cout << "Is Sell : YES = 1, NO = 0" << endl;
		cout << "Enter new state >> ";
		cin >> isSell;
		cin.ignore();
		stateProduct[id][1] = isSell;
		writeFile();
		break;
	default:
		break;
	}
}
void Store::updateInventory(int id)
{
	int inventory = stateProduct[id][0];
	if ((inventory - 1) > 0) {
		stateProduct[id][0] = --inventory;
	}
	else {
		if (inventory - 1 == 0) {
			stateProduct[id][0] = --inventory;
			cout << "product number " << id << "is SoldOut. Check Inventory" << endl;
			stateProduct[id][1] = 0;
		}
		else
		{
			cout << "product number " << id << "is SoldOut. Check Inventory" << endl;
			stateProduct[id][1] = 0;
		}

	}
	writeFile();
}
vector<int> Store::getSellList()
{
	readFile();
	vector <int> sellList;
	for (const auto& v : stateProduct)
	{
		if (v.second[1] == 1) {
			sellList.push_back(v.first);
		}

	}
	return sellList;
}


int Store::getInventory(int id)
{

	return stateProduct[id][0];
}


vector<string> Store::parseCSV(istream& file, char delimiter)
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
void Store::displayInfo()
{
	readFile();
	cout << endl << "  ID  |     Inventory     | IsSell(Y/N) " << endl;
	for (const auto& v : stateProduct) {
		cout << setw(5) << setfill('0') << right << v.first << " | " << left;
		cout << setw(12) << setfill(' ') << v.second[0] << " | ";
		if (v.second[1] == 1)
		{
			cout << setw(12) << "Y" << endl;
		}
		else {
			cout << setw(12) << "N" << endl;
		}

	}
}
bool Store::displayMenu()
{
	int quit = 0;
	ProductManager pm;
	readFile();//!!!

	while (quit != 1) {
		int ch;
		//cout << "\033[2J\033[1;1H";
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "                   Store Menu                " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "  1. Display Product State List              " << endl;
		cout << "  2. Add Product State                       " << endl;
		cout << "  3. Modify Product State                    " << endl;
		cout << "  4. Quit this Program                       " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		writeFile();
		readFile();
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
			addState();
			break;
		case 3:
			displayInfo();
			updateStatet();
			break;
		case 4:
			quit = 1;
			break;
		}

	}
	return true;
}