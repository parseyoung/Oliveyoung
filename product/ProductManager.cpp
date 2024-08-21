#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>

#include "ProductManager.h"
#include "Product.h"
#include "../Manager.h"

using namespace std;

ProductManager::ProductManager()
{
    load();
}

ProductManager::~ProductManager()
{
    // 동적으로 할당된 Product 객체를 삭제
    for (auto& pair : mProductMap) {
        delete pair.second;
    }
    mProductMap.clear(); // 맵을 비우고, 모든 요소를 제거
}

ProductManager::ProductManager(const ProductManager& other)
{
    // 깊은 복사: 다른 객체의 Product들에 대해 새로운 Product 객체를 생성
    for (const auto& pair : other.mProductMap) {
        // Product를 복사하여 새로운 메모리 공간에 저장
        mProductMap[pair.first] = new Product(*(pair.second));
    }
}
    
// 데이터 관리 
const bool ProductManager::add(const Product& product)
{
    Product* pProduct = new Product(product.getId(), product.getName(), product.getPrice(), product.getCategory());
    
    pair<map<unsigned int, Product*>::iterator, bool> result = 
        mProductMap.insert(make_pair(product.getId(), pProduct));
    if (result.second == false) { // 키 중복인 경우 실패
        delete pProduct;
        return false;
    }

    appendToFile(product);

    return true;
}

const bool ProductManager::remove(const unsigned int id)
{
    auto it = mProductMap.find(id);
    if (it == mProductMap.end()) {
        cout<<"remove ERrro!!!"<<endl;
        return false;
    }

    delete it->second;    // 메모리 해제
    mProductMap.erase(it); // Product 삭제
    
    removeFromFile(id);   // 파일에서 Product 제거

    return true;
}

const Product* ProductManager::getByIdOrNull(const unsigned int id) const
{
    auto iter = mProductMap.find(id);
    if (iter == mProductMap.end()) {
        return nullptr;
    }

    return (iter->second);
}

const bool ProductManager::contains(const unsigned int id) const
{
    auto iter = mProductMap.find(id);
    if (iter == mProductMap.end()) {
        return false;
    }
    return true;
}

// 저장소 관리
void ProductManager::load()
{
    cout<< "load PRoduct Manager"<<endl;
    ifstream fin;
    fin.open(ProductManagerConstants::RESOURCE);
    if(fin.fail() == true) {
        cerr << "[ProductManager] Fail: open file for reading" << endl;
        return ;
    }

    while(fin.eof() == false) {
        vector<string> tokens = parseCSV(fin, ',');
        if(tokens.size()) {
            unsigned int id = atoi(tokens[0].c_str());
            // string name = tokens[1];
            int price = atoi(tokens[2].c_str());
            // int category = atoi(tokens[3].c_str());
            Product* product = new Product(id, tokens[1], price, tokens[3]);
            mProductMap.insert(make_pair(id, product));
        }
    }
    
    fin.close( );
}

// void clearConsole() {
//     system("clear");
//     // cout << "\033[2J\033[1;1H";
// }

// View 관리
const bool ProductManager::displayMenu()
{
    enum MenuOptions { DISPLAY_CLIENT_LIST = 1, INPUT_CLIENT, DELETE_CLIENT, QUIT_PROGRAM };

    // clearConsole();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    
    int id;
    int menu;
    cin >> menu;
    switch(menu) {
        case DISPLAY_CLIENT_LIST: 
            // clearConsole();

            displayInfo();
            cin.ignore();
            getchar();

            break;
        case INPUT_CLIENT:
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Input Product (name)" << endl;
            cout << setw(45) << setfill('-') << "\n" << endl;
            inputItem();

            break;
        case DELETE_CLIENT:
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Delete Product" << endl;;
            cout << setw(45) << setfill('-') << "\n" << endl;

            displayInfo();
            cout << "   Choose product id : ";

            cin >> id;
            remove(id);

            break;
        case QUIT_PROGRAM:
            return true;

        default:
            cout << DISPLAY_CLIENT_LIST << "와 " << QUIT_PROGRAM << " 사이의 값을 입력하세요." << endl;
            break;
    }

    return false;
}

void ProductManager::displayInfo() const
{
    cout << "Product list" << endl;
    cout << endl << "  ID  |     Name     " << endl;
    for (const auto& it : mProductMap) {
        Product* product = it.second;
        cout << setw(5) << setfill('0') << right << product->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << product->getName() << endl;
        cout << setw(12) << setfill(' ') << product->getPrice() << endl;
        cout << setw(12) << setfill(' ') << product->getCategory() << endl;
    }

    cout << endl;
    cout << "return to menu: enter any key" << endl;
}

void ProductManager::inputItem()
{
    string name;
    int price;
    string category;
    cout << "name : "; cin >> name;
    cout << "price : "; cin >> price;
    cout << "category : "; cin >> category;
    // validate field

    add(Product(generateId(), name, price, category));
}
const unsigned int ProductManager:: generateId() const
{
     if (mProductMap.size() == 0) {
        return 0;
    } else {
        auto elem = mProductMap.end(); 
        int id = (--elem)->first;
        return ++id;
    }
}
void ProductManager::appendToFile(const Product& product) const
{
    ofstream fout;
    fout.open(ProductManagerConstants::RESOURCE, ios_base::app);
    if (fout.is_open() == false) {
        cerr << "[ProductManager] Fail: open file for writing" << endl;
        return; 
    }

    cout << product.toString() << endl;
    fout << product.toString() << endl;

    fout.close();
}

void ProductManager::removeFromFile(const unsigned int id) const
{
    ifstream fin;
    fin.open(ProductManagerConstants::RESOURCE);
    if (fin.is_open() == false) {
        cerr << "[ProductManager] Unable to open file for reading" << endl;
        return;
    }

    ofstream fout;
    fout.open(TEMP_BUFFER.c_str());  // 임시 파일을 쓰기 모드로 엽니다.
    if (fout.is_open() == false) {
        cerr << "[ProductManager] Unable to open temporary file for writing" << endl;
        fin.close();
        return;
    }


    string line;
    bool found = false;

    while (getline(fin, line)) {
        try {
            Product product = Product::createFromString(line);
            if (product.getId() == id) {
                found = true;
                // 제거할 Product는 기록하지 않고 넘어갑니다.
                continue;
            }
            fout << line << endl;  // 제거할 Product가 아니면 기록합니다.
        } catch (const invalid_argument&) {
            fout << line << endl;  // Product 생성에서 예외가 발생하면 기록합니다.
        }
    }

    fin.close();
    fout.close();

    if (found == true) {
        std::remove(ProductManagerConstants::RESOURCE.c_str());  // 원본 파일을 삭제합니다.
        rename(TEMP_BUFFER.c_str(), (ProductManagerConstants::RESOURCE).c_str());  // 임시 파일을 원본 파일 이름으로 변경합니다.
    } else {
        std::remove(TEMP_BUFFER.c_str());  // 제거할 Product가 없으면 임시 파일을 삭제합니다.
    }
}
