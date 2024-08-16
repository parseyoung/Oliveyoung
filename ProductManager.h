#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "Product.h"
#include "CategoryManager.h"
#include <map>
#include <vector>
#include <string>

class ProductManager
{
public:
	ProductManager(CategoryManager& categoryManager);
	~ProductManager();

	void loadProductsFromFile();
	void saveProductsToFile();

	void addProduct(const string& categoryName, const string& name, int price, int quantity);
	void deleteProduct(int id);
	Product* searchProduct(int id) const;

	void displayProducts() const;
	bool displayMenu();
	

private:
	int makeId();
	vector<string> parseCSV(std::istream& file, char delimiter);

	map<int, Product*> mProductMap;
	CategoryManager& mCategoryManager; 

	
};

#endif // PRODUCTMANAGER_H
