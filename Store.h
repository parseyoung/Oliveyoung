//-map : 상품 상태(재고, 판매 여부)관리
//- { 상품: (재고, 판매여부) }
//- vector : 판매내역
//- 파일을 일별로 저장하는거임
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
	void addState();//add추가=> 제품 추가됬을 때 
private:
	map<int, vector<int>> stateProduct;

};
#endif