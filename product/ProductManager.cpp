#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "ProductManager.h"
#include "Product.h"
#include "../Validation/Validation.h"


using namespace std;

// ProductManager 생성자: 프로그램 시작 시 상품 목록을 파일에서 불러옴
ProductManager::ProductManager()
{
    load();
}

// ProductManager 소멸자: 모든 동적으로 할당된 Product 객체를 삭제
ProductManager::~ProductManager()
{
    for (auto& pair : mProductMap) {
        delete pair.second; // 객체 메모리 해제
    }
    mProductMap.clear(); // 맵을 비우고, 모든 요소를 제거
}

// 복사 생성자: 깊은 복사를 통해 다른 ProductManager 객체의 모든 Product를 복사
ProductManager::ProductManager(const ProductManager& other)
{
    for (const auto& pair : other.mProductMap) {
        // Product를 복사하여 새로운 메모리 공간에 저장
        mProductMap[pair.first] = new Product(*(pair.second));
    }
}
    
// Product 추가
bool ProductManager::add(const Product& product)
{
    bool result = BaseEntity<Product>::add(product);
    if (result) {
        appendToFile(product);
    }
}
// Product 제거
bool ProductManager::remove(const unsigned int id)
{
    bool result = BaseEntity<Product>::remove(id);  // BaseEntity의 remove 메소드 호출

    if (result) {
        removeFromFile(id);   // 파일에서 상품 제거
    }

    return result;
}

// ID로 Product 검색: 해당 ID의 Product가 있으면 반환, 없으면 nullptr 반환
const Product* ProductManager::getByIdOrNull(const unsigned int id) const
{
    auto iter = mProductMap.find(id);
    if (iter == mProductMap.end()) {
        return nullptr;
    }

    return (iter->second);
}

// 해당 ID의 Product가 존재하는지 확인
const bool ProductManager::contains(const unsigned int id) const
{
    auto iter = mProductMap.find(id);
    if (iter == mProductMap.end()) { // 해당 ID의 Product가 없는 경우
        return false;
    }
    return true;
}

// 파일에서 제품 목록을 불러와서 맵에 저장
void ProductManager::load()
{
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

// 메뉴를 화면에 표시하고 사용자의 입력을 처리
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

            displayItemsInfo();
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

            displayItemsInfo();
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
// 저장된 모든 Product의 정보를 화면에 표시
void ProductManager::displayItemsInfo() const
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
// 사용자로부터 제품 정보를 입력받아 Product를 추가
void ProductManager::inputItem() {
    string name;
    int price;
    string category;

    // 제품 이름 유효성 검사
    while (true) {
        cout << "name : "; cin >> name;
        if (Validation::validateProductName(name)) {
            break;
        }
    }

    // 제품 가격 유효성 검사
    while (true) {
        cout << "price : "; cin >> price;
        if (cin.fail()) {
            cin.clear(); // 입력 스트림을 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력을 무시
            cout << "Error: Price must be a non-negative integer." << endl;
        }
        else if (Validation::validateProductPrice(price)) {
            break;
        }
    }

    // 제품 카테고리 유효성 검사
    while (true) {
        cout << "category : "; cin >> category;
        if (Validation::validateProductCategory(category)) {
            break;
        }
    }

    // Product를 추가
    add(Product(generateId(), name, price, category));
}

// 새로운 Product ID를 생성
unsigned int ProductManager::generateId() const
{
    return BaseEntity<Product>::generateId(mProductMap);
}

// CSV 파일을 파싱하여 벡터에 각 요소를 저장
vector<string> ProductManager::parseCSV(istream& fin, char delimiter)
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
// Product 정보를 파일에 추가
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

// 파일에서 특정 ID의 Product를 제거
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
            fout << line << endl;  // Product 생성에서 예외가 발생하ㅁ면 기록합니다.
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
