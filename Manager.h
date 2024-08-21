#ifndef _MANAGER_H__
#define _MANAGER_H__
#include <string>
#include <map>
#include <vector>
#include "database/Constants.h"
using namespace std;

namespace ManagerConstants{
    const string RESOURCE = DIR_DATABASE + "object_list.csv";
}

class Manager
{
    public:
    virtual ~Manager();
    // 데이터 관리 
    template<typename T1> 
    const bool add(const T1 &newObject);//overloading
    const void remove(const string removeFile)const;//overloading
    template<typename T1, typename T2>
    const T1* getByIdOrNull(T2 id) const;//overloading

    // 저장소 관리
    virtual void load() = 0;

    // View 관리
    virtual const bool displayMenu() const ;//overriding
    virtual void displayInfo() const=0;//overriding
    virtual void inputItem();//overriding
    
    protected:
    template<typename T1>
    void appendToFile(const T1& object) const;//overloading
    virtual void removeFromFile(const unsigned int id) const = 0;//overriding
    virtual const unsigned int generateId() const;//overloading
    vector<string> parseCSV(istream& fin, char delimiter);//use parent's function original
    private:
    map <unsigned int, string*> mObjectMap;
};
#endif