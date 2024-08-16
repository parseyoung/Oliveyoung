//-정보
//- 추가
//- 삭제
#ifndef _PRODUCTMANAGER_H__
#define _PRODUCTMANAGER_H__
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>
#include<map>
using namespace std;
class Product;
class ProductManager
{
public:
	ProductManager();
	~ProductManager();
	void addProduct(Product* adProduct);
	void deleteProduct();
	void inputProduct();
	void updateProduct();
	vector<string> parseCSV(istream& file, char delimiter);
	bool displayMenu();
	void displayInfo();
	void readFile();
	map<int, Product*> getList();
	void writeFile();
	vector <int> getIdList();
	void makeIdList();
	bool isExist(int id);

private:
	map<int, Product*> productList;
	vector<int> idList;
};

#endif