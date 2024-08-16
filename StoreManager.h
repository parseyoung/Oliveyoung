#ifndef __STOREMANAGER_H__
#define __STOREMANAGER_H__
#include<vector>
#include<string>
#include<istream>
using namespace std;
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
	void record();
	vector<string> parseCSV(istream& file, char delimiter);
	void showTodayRecord();
private:
	map<int, vector<string>> sellItems;
	map<int, vector<string>> todayRecord;

};
#endif