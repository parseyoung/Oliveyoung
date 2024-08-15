#ifndef __STOREMANAGER_H__
#define __STOREMANAGER_H__
class StoreManager
{
public:
	StoreManager();
	~StoreManager();
	void sell();
	void record();
	void displayInfo();
private:
	map<int, pair<string, vector<int>>> sellItems;

};
#endif