#include "product.h"
Product::Product()
{
	mId = 0;
	mName = "";
	mPrice = 0;
	mCategory = "";
}
Product::Product(int id, string name, int price, string category)
{
	mId = id;
	mName = name;
	mPrice = price;
	mCategory = category;
}
Product :: ~Product()
{
}
int Product::getId()
{
	return mId;
}
string Product::getName()
{
	return mName;
}
int Product::getPrice()
{
	return mPrice;
}
string Product::getCategory()
{
	return mCategory;
}
void Product::setId(int id)
{
	mId = id;
}
void Product::setName(string name)
{
	mName = name;
}
void Product::setPrice(int price)
{
	mPrice = price;
}
void Product::setCategory(string category)
{
	mCategory = category;
}