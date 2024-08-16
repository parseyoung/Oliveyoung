#ifndef __STOREMANAGER_H__
#define __STOREMANAGER_H__
class StoreManager
{
public:
	StoreManager();
	~StoreManager();
	void sell();
	//void record();
	void displayInfo();
	bool displayMenu();
	void readFile();
	void inputUserId();
private:
	map<int, vector<string>> sellItems;

};
#endif