//-map : ��ǰ ����(���, �Ǹ� ����)����
//- { ��ǰ: (���, �Ǹſ���) }
//- vector : �Ǹų���
//- ������ �Ϻ��� �����ϴ°���
#ifndef _STORE_H_
#define _STORE_H_

#include<map>
#include<vector>
using namespace std;
class Product;
class Store
{
public:
	Store();
	~Store();
	vector<string> parseCSV(istream& file, char delimiter);
	void updateStatet();
	void displayInfo();
	bool displayMenu();
	void readFile();
	void writeFile();
	vector<int> getSellList();
	int getInventory(int id);
	void updateInventory(int id);
	void addState();//add�߰�=> ��ǰ �߰����� �� 
private:
	map<int, vector<int>> stateProduct;

};
#endif