#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <iostream>
#include <list>

#include "../observer/Subject.h"
#include "../observer/Observer.h"
#include "../database/Constants.h"

using namespace std;

template<typename T>
class BaseManager : public Subject
{
public:
    BaseManager(const string& resourcePath);
    ~BaseManager();
    
    const bool add(const T& item);
    const bool remove(const unsigned int id);
    const T& getById(const unsigned int id) const;
    const bool contains(const unsigned int id) const;
    void subscribe(Observer *o);
    void unsubscribe(Observer *o);

    void load();

protected:
    const unsigned int generateId() const;
    map<unsigned int, T*> mItemMap;
    list<Observer*>observers;
private:
    vector<string> parseCSV(istream& fin, char delimiter);
    void appendToFile(const T& item) const;
    void removeFromFile(const unsigned int id) const;

    string mResourcePath;
};




template <typename T>
BaseManager<T>::BaseManager(const std::string& mResourcePath) 
    : mResourcePath(mResourcePath)
{
    load();
}

template <typename T>
BaseManager<T>::~BaseManager()
{
    for (auto& pair : mItemMap) {
        delete pair.second;
    }
    mItemMap.clear();
}
    
template <typename T>
const bool BaseManager<T>::add(const T& item) {
    T* pItem = new T(item);

    // 'typename' 키워드를 사용하여 템플릿 클래스의 내부 타입을 명시
    typename map<unsigned int, T*>::iterator it;
    pair<typename map<unsigned int, T*>::iterator, bool> result = 
        mItemMap.insert(make_pair(item.getId(), pItem));

    if (result.second == false) {
        delete pItem;
        return false;
    }

    appendToFile(item);

    return true;
}

template <typename T>
const bool BaseManager<T>::remove(const unsigned int id)
{
    auto it = mItemMap.find(id);
    if (it == mItemMap.end()) {
        return false;
    }

    delete it->second;   
    mItemMap.erase(it);

    removeFromFile(id);

    return true;
}

template <typename T>
const T& BaseManager<T>::getById(const unsigned int id) const
{
    auto iter = mItemMap.find(id);
    if (iter == mItemMap.end()) {
        throw std::out_of_range("T with the given ID not found.");
    }

    return *(iter->second);
}

template <typename T>
const bool BaseManager<T>::contains(const unsigned int id) const
{
    auto iter = mItemMap.find(id);
    if (iter == mItemMap.end()) {
        return false;
    }
    return true;
}

// 저장소 관리
template <typename T>
void BaseManager<T>::load()
{
    ifstream fin;
    fin.open(mResourcePath);
    if(fin.fail() == true) {
        cerr << "Fail: open file for reading" << endl;
        return ;
    }

    string line;
    while (std::getline(fin, line)) {
        try {
            T item = T::createFromString(line);
            mItemMap.insert(std::make_pair(item.getId(), new T(item)));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
            // 오류 발생 시 해당 라인을 무시하거나 다른 처리 수행
        }
    }
    
    fin.close( );
}

template <typename T>
const unsigned int BaseManager<T>::generateId() const
{
    // 로직의 수정이 필요할듯
    if (mItemMap.size() == 0) {
        return 0;
    } else {
        auto elem = mItemMap.end(); 
        int id = (--elem)->first;
        return ++id;
    }
}

template <typename T>
vector<string> BaseManager<T>::parseCSV(istream& fin, char delimiter)
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
}

template <typename T>
void BaseManager<T>::appendToFile(const T& item) const
{
    ofstream fout;
    fout.open(mResourcePath, ios_base::app);
    if (fout.is_open() == false) {
        cerr << "Fail: open file for writing" << endl;
        return; 
    }

    cout << item.toString() << endl;
    fout << item.toString() << endl;

    fout.close();
}

template <typename T>
void BaseManager<T>::removeFromFile(const unsigned int id) const
{
    ifstream fin;
    fin.open(mResourcePath);
    if (fin.is_open() == false) {
        cerr << "Unable to open file for reading" << endl;
        return;
    }

    ofstream fout;
    fout.open(TEMP_BUFFER.c_str());
    if (fout.is_open() == false) {
        cerr << "Unable to open temporary file for writing" << endl;
        fin.close();
        return;
    }


    string line;
    bool found = false;

    while (getline(fin, line)) {
        try {
            T item = T::createFromString(line);
            if (item.getId() == id) {
                found = true;
                continue;
            }
            fout << line << endl;  
        } catch (const invalid_argument&) {
            fout << line << endl;
        }
    }

    fin.close();
    fout.close();

    if (found == true) {
        std::remove(mResourcePath.c_str());
        rename(TEMP_BUFFER.c_str(), (mResourcePath).c_str());
    } else {
        std::remove(TEMP_BUFFER.c_str());
    }
}
template <typename T>
void BaseManager<T>::subscribe(Observer *o)
{
    observers.push_back(o);
}
template <typename T>
void BaseManager<T>::unsubscribe(Observer *o)
{
    delete o;
    observers.remove(o);
    
}

#endif // BASE_MANAGER_H

