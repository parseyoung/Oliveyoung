#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "StoreManager.h"
#include "Purchase.h"

using namespace std;

Logger StoreManager::logger("StoreManager");

StoreManager::StoreManager(Store& store, ProductManager& productManager, ClientManager& clientManager)
    : mStore(store)
    , mProductManager(productManager) 
    , mClientManager(clientManager) 
{
    loadStockInfo();
}

StoreManager::~StoreManager() 
{
}

StoreManager::StoreManager(const StoreManager& other)
    : mStore(other.mStore)
    , mProductManager(other.mProductManager)
    , mClientManager(other.mClientManager)
{
}

const bool StoreManager::setQuantity(const Product& product, const unsigned int quantity)
{
    auto& stockMap = mStore.getProductStockMap();
    auto it = stockMap.find(product.getId());
    if (it != stockMap.end()) {
        it->second.setQuantity(quantity);
        return true;
    }
    return false;
}


const bool StoreManager::setAvailability(const Product& product, const bool availability) 
{
    auto& stockMap = mStore.getProductStockMap();
    auto it = stockMap.find(product.getId());
    if (it != stockMap.end()) {
        it->second.setAvailability(availability);
        return true;
    }
    return false;
}

const bool StoreManager::sell(const unsigned int productId, const unsigned int clientId) 
{
    logger.info("sell() called with productId: " + to_string(productId) + ", clientId: " + to_string(clientId));

    auto& stockMap = mStore.getProductStockMap();
    auto it = stockMap.find(productId);
    if (it != stockMap.end() 
        && it->second.getQuantity() > 0 && it->second.isAvailable() == true) {
        unsigned int qauntity = it->second.getQuantity();
        it->second.setQuantity(qauntity - 1);  // 재고 감소

        logger.info("Decreased product quantity. New quantity: " + to_string(it->second.getQuantity()));
        // CSV 파일에서 해당 제품의 재고 업데이트
        updateStockInfoInFile(productId, it->second);

        // 구매 내역 기록
        recordPurchase(productId, clientId);
        logger.info("Recorded purchase for productId: " + to_string(productId) + ", clientId: " + to_string(clientId));

        return true;
    }
    logger.warning("Product not found in stock map for productId: " + to_string(productId));

    return false;
}

void StoreManager::recordPurchase(const unsigned int productId, const unsigned int clientId) const
{
    Purchase purchase = Purchase(productId, clientId);

    ofstream fout;
    fout.open(PURCHASE_HISTORY, ios_base::app);
    if (fout.is_open() == false) {
        logger.error("Failed to open purchase history file for writing");
        return;
    }

    fout << purchase.toString() << endl;

    fout.close();

    logger.info("Successfully recorded purchase for productId: " + to_string(productId) + ", clientId: " + to_string(clientId));
}


void StoreManager::updateStockInfoInFile(const unsigned int productId, const StockInfo& updatedStockInfo) const 
{
    logger.info("Updating stock info in file for productId: " + to_string(productId));
 
    ifstream fin;
    fin.open(STOCK_INFO.c_str(), ios_base::app);
    if (fin.is_open() == false) {
        logger.error("Failed to open stock info file for reading");
        return;
    }

    ofstream fout;
    fout.open(TEMP_BUFFER.c_str());
    if (fout.is_open() == false) {
        logger.error("Failed to open temporary file for writing");
        fin.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(fin, line)) {
        istringstream iss(line);
        unsigned int id;
        char comma;

        if (!(iss >> id >> comma) || comma != ',') {
            fout << line << endl;  // 올바른 형식이 아니면 그대로 작성
            continue;
        }

        if (id == productId) {
            fout << Store::toStockInfoString(productId, updatedStockInfo) << endl;  // 업데이트된 재고 정보 기록
            found = true;
        } else {
            fout << line << endl;  // 다른 제품 정보는 그대로 유지
        }
    }

    // 만약 파일에서 해당 productId를 찾지 못했다면 추가
    if (found == false) {
        logger.info("ProductId not found in stock info file. Adding new record.");
        fout << Store::toStockInfoString(productId, updatedStockInfo) << endl;
        cout << "추가 완료" << endl;
    }

    fin.close();
    fout.close();

    remove(STOCK_INFO.c_str());  // 원본 파일 삭제
    rename(TEMP_BUFFER.c_str(), STOCK_INFO.c_str());  // 임시 파일을 원본 파일로 교체
}


void StoreManager::loadStockInfo() 
{
    ifstream fin;
    fin.open(STOCK_INFO);
    if(fin.fail() == true) {
        logger.error("Failed to open stock info file for reading");
        return ;
    }

    map<unsigned int, StockInfo> stockMap;
    string line;
    while (getline(fin, line)) {
        try {
            auto productStockPair = Store::createStockInfoFromString(line);
            stockMap[productStockPair.first] = productStockPair.second;
        } catch (const exception& e) {
            logger.error("Error parsing line: " + string(e.what()));
        }
    }
    fin.close();
    logger.info("Stock info loaded successfully");

    mStore.initialize(stockMap);
}


// CSV 파싱 함수
vector<string> StoreManager::parseCSV(istream& fin, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while(fin.eof() == false) {
        char ch = fin.get();
        if (ch == delimiter || ch == '\r' || ch == '\n') {
            if(fin.peek()=='\n') fin.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t)+1);
            row.push_back(s);
            ss.str("");

            if (ch != delimiter) {
                break;
            }
        } else {
            ss << ch;
        }
    }
    return row;
}

// 파일에 데이터 추가
void StoreManager::appendStockInfoToFile(const unsigned int productId, const StockInfo& stockInfo) const 
{
    ofstream fout;
    fout.open(STOCK_INFO, ios_base::app);
    if (fout.is_open() == false) {
        logger.error("Failed to open the store data file for appending.");
        return;
    }

    fout << Store::toStockInfoString(productId, stockInfo) << endl;

    fout.close();
}

// 파일에서 데이터 삭제
void StoreManager::removeStockInfoFromFile(const unsigned int id) const
{
    ifstream fin;
    fin.open(STOCK_INFO);
    if (fin.is_open() == false) {
        logger.error("Unable to open stock info file for reading");
        return;
    }

    ofstream fout;
    fout.open(TEMP_BUFFER.c_str());  // 임시 파일을 쓰기 모드로 엽니다.
    if (fout.is_open() == false) {
        logger.error("Unable to open temporary file for writing");
        fin.close();
        return;
    }

    string line;
    bool found = false;

    while (getline(fin, line)) {
        try {
            auto productStockPair = Store::createStockInfoFromString(line);
            if (productStockPair.first == id) {
                found = true;
                // 제거할 항목이므로 기록하지 않습니다.
                continue;
            }
            fout << line << endl;  // 제거할 항목이 아니면 파일에 기록합니다.
        } catch (const invalid_argument&) {
            fout << line << endl;  // 예외 발생 시 그대로 기록합니다.
        }
    }

    fin.close();
    fout.close();

    if (found) {
        remove(STOCK_INFO.c_str());  // 원본 파일을 삭제합니다.
        rename(TEMP_BUFFER.c_str(), STOCK_INFO.c_str());  // 임시 파일을 원본 파일 이름으로 변경합니다.
    } else {
        remove(TEMP_BUFFER.c_str());  // 제거할 항목이 없으면 임시 파일을 삭제합니다.
    }
}

// 메뉴 표시
const bool StoreManager::displayMenu()
{
    enum MenuOptions { SELL_PRODUCT = 1, DISPLAY_STOCK_INFO, DISPLAY_PURCHASE_HISTORY, SET_STOCK_IFNFO, QUIT_PROGRAM };

    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "            Store Management Menu            " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Sell Product                            " << endl;
    cout << "  2. Display Stock Info                      " << endl;
    cout << "  3. Display Purchase history                " << endl;
    cout << "  4. Set Stock and Availability              " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";

    int menu;
    cin >> menu;
    switch(menu) {
        case SELL_PRODUCT: 
            handleSellProduct();
            break;

        case DISPLAY_STOCK_INFO: 
            displayStockInfo();
            break;

        case DISPLAY_PURCHASE_HISTORY: 
            displayPurchaseHistory();
            break;

        case SET_STOCK_IFNFO: 
            setStockInfo();
            break;

        case QUIT_PROGRAM:
            return true;

        default:
            cout << "Please enter a number between " << SELL_PRODUCT << " and " << QUIT_PROGRAM << "." << endl;
            break;
    }

    return false;
}

void StoreManager::setStockInfo()
{
    unsigned int productId;
    unsigned int newQuantity;
    bool availability;

    cout << "Enter the Product ID: ";
    cin >> productId;

    cout << "Enter new quantity: ";
    cin >> newQuantity;

    cout << "Set availability (1 for available, 0 for not available): ";
    cin >> availability;

    // Get the map of product stock
    map<unsigned int, StockInfo>& stockMap = mStore.getProductStockMap();

    // Check if the product ID exists in the stock map
    auto it = stockMap.find(productId);
    if (it != stockMap.end()) {
        // Update the stock info if the product already exists
        it->second.setQuantity(newQuantity);
        it->second.setAvailability(availability);
        cout << "Stock information updated successfully." << endl;
    } else {
        // If product ID not found in stock map, check with ProductManager
        if (mProductManager.contains(productId)) {
            // Add new stock info to the stock map
            StockInfo newStockInfo = StockInfo(newQuantity, availability);
            stockMap[productId] = newStockInfo;
            cout << "Product ID added to stock map and stock information updated successfully." << endl;
        } else {
            cout << "Product ID not found in Product Manager. Please check the Product ID and try again." << endl;
            return;
        }
    }

    // Save the updated or new stock info to the file
    updateStockInfoInFile(productId, stockMap[productId]);
}



void StoreManager::handleSellProduct()
{
    unsigned int productId;
    unsigned int clientId;

    cout << "Enter Product ID to sell: ";
    cin >> productId;
    
    cout << "Enter Client ID: ";
    cin >> clientId;

    if (sell(productId, clientId)) {
        cout << "Product sold successfully!" << endl;

        // appendPurchaseToFile(productId, clientId);

        // // 구매 내역 기록
        // recordPurchase(productId, clientId);
    } else {
        cout << "Failed to sell product. Check if product is available and in stock." << endl;
    }
}

void StoreManager::displayStockInfo() const
{
    auto& stockMap = mStore.getProductStockMap();
    
    if (stockMap.empty()) {
        cout << "No stock information available." << endl;
        return;
    }

    cout << "Product ID | Quantity | Availability" << endl;
    cout << "--------------------------------------" << endl;
    
    for (const auto& entry : stockMap) {
        cout << entry.first << " | " 
             << entry.second.getQuantity() << " | " 
             << (entry.second.isAvailable() ? "Available" : "Not Available") 
             << endl;
    }
}

void StoreManager::appendPurchaseToFile(unsigned int productId, unsigned int clientId) const
{
    // 현재 날짜와 시간 가져오기
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateStr[20];
    snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d %02d:%02d:%02d",
             1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
             ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    ofstream file(PURCHASE_HISTORY, ios_base::app);

    if (file.is_open() == false) {
        logger.error("Failed to open purchase history file for appending.");
        return;
    }

    file << productId << "," << clientId << "," << dateStr << endl;
    file.close();
}


void StoreManager::displayPurchaseHistory() const
{
    ifstream fin;
    fin.open(PURCHASE_HISTORY);

    if (fin.is_open() == false) {
        logger.error("Failed to open purchase history file.");
        return;
    }

    string line;
    cout << "Purchase History" << endl;
    cout << "-----------------" << endl;
    cout << left
         << setw(12) << "Client ID"
         << setw(15) << "Product ID"
         << setw(20) << "Date"
         << endl;


    while (getline(fin, line)) {
        try {

            Purchase purchase = Purchase::createPurchaseFromString(line);

            // Print in formatted way
            cout << left
                    << setw(12) << purchase.getClientId()
                    << setw(15) << purchase.getProductId()
                    << setw(20) << Purchase::timePointToString(purchase.getDate())
                    << endl;

        } catch (const std::invalid_argument& e) {
            logger.error("Error parsing purchase history line: " + string(e.what()));
        }
    }

    fin.close();
}
