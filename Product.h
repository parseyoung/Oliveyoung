//## ��ǰ
/*-id : int
- �̸� : string
- ���� : int
- ī�װ� : string �� Ŭ����ȭ*/


#ifndef __PRODUCT_H__
#define __PRODUCT_H__
#include<string>
using namespace std;
class Product
{
public:
	Product();
	Product(int id, string name, int price, string category);
	~Product();
	int getId();
	string getName();
	int getPrice();
	string getCategory();
	void setId(int id);
	void setName(string name);
	void setPrice(int id);
	void setCategory(string category);
private:
	int mId;
	string mName;
	int mPrice;
	string mCategory;
};

#endif