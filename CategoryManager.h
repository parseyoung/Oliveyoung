#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include "Category.h"
#include <map>
#include <string>
#include <vector> 

class CategoryManager
{
public:
	CategoryManager();
	~CategoryManager();

	void addCategory(const std::string& categoryName);
	void deleteCategory(const std::string& categoryName);
	Category* getCategory(const string& categoryName) const;
	void displayCategories() const;

	void loadCategoriesFromFile();
	void saveCategoriesToFile() const;
	vector<string> parseCSV(istream& file, char delimiter);


private:
	map<string, Category*> mCategoryMap;
};

#endif // CATEGORYMANAGER_H
