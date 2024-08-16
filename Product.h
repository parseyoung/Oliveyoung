#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
using namespace std;

class Product
{
public:
	Product(int id, const string& categoryName, const string& name, int price, int quantity);
	~Product();
	void displayInfo() const;
	int getId() const;
	string getName() const;
	int getPrice() const;
	int getQuantity() const;
	void setQuantity(int quantity);
	string getCategory() const;

private:
	int mId;
	string mName;
	string mCategory;
	int mPrice;
	int mQuantity;
};

#endif // PRODUCT_H