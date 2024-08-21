#include "Manager.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

Manager :: ~Manager()
{}
template<typename T1>
const bool Manager :: add(const T1& newObject)
{
    T1* pObject = new T1(newObject);
    int id = 1234;
    pair<map<unsigned int, string*>::iterator, bool> result = 
        mObjectMap.insert(make_pair(id, pObject));
    if (result.second == false) { // 키 중복인 경우 실패
        delete pObject;
        return false;
    }

    appendToFile(newObject);

    return true;
}//overloading
const void Manager:: remove(const string removeFile) const
{
    std::remove(removeFile.c_str());
}
template<typename T1, typename T2>
const T1* Manager :: getByIdOrNull(T2 id) const
{
    auto iter = mObjectMap.find(stoi(id));
    if (iter == mObjectMap.end()) {
        return nullptr;
    }

    return (iter->second);
}//overloading

template<typename T1>
void Manager::appendToFile(const T1& object) const
{
    ofstream fout;
    fout.open(ManagerConstants::RESOURCE, ios_base::app);
    if (fout.is_open() == false) {
        cerr << "[Manager] Fail: open file for writing" << endl;
        return; 
    }

    cout << object.toString() << endl;
    fout << object.toString() << endl;

    fout.close();
}
const unsigned int Manager:: generateId() const
{
     if (mObjectMap.size() == 0) {
        return 0;
    } else {
        auto elem = mObjectMap.end(); 
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> Manager :: parseCSV(istream& fin, char delimiter)
{
     stringstream ss;
    vector<string> tokens;
    string t = " \n\r\t";

    while(fin.eof() == false) {
        char ch = fin.get();
        if (ch == delimiter || ch == '\r' || ch == '\n') {
            if(fin.peek()=='\n') fin.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t)+1);
            tokens.push_back(s);
            ss.str("");

            if (ch != delimiter) {
                break;
            }
        } else {
            ss << ch;
        }
    }
    return tokens;
}//use parent's function original
const bool Manager :: displayMenu() const 
{
    cout<<"Manager function call!!"<<endl;
    return false;
}//overriding
void Manager :: inputItem()
{
    cout<<"Manager function call!!"<<endl;
}//overriding