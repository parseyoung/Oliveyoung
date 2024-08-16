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
private:
	map<int, vector<string>> sellItems;

};
#endif