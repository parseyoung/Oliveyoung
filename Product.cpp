#include "Product.h"

Product::Product(int id,  const string& categoryName, const string& name, int price, int quantity)
	: mId(id), mCategory(categoryName), mName(name), mPrice(price), mQuantity(quantity) {}

Product::~Product() {}
void Product::displayInfo() const
{
	cout << "ID : " << mId << "Category : " << mCategory <<  ", mName : " << mName << ", Price : " << mPrice << ", Quantity : " << mQuantity << endl;
}

int Product::getId() const
{
	return mId;
}

string Product::getName() const
{
	return mName;
}

int Product::getPrice() const
{
	return mPrice;
}

int Product::getQuantity() const
{
	return mQuantity;
}
void Product::setQuantity(int quantity) 
{ 
	mQuantity = quantity;
}

string Product::getCategory() const
{
	return mCategory;
}