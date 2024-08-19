#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>

#include "ClientManager.h"
#include "Client.h"

using namespace std;

ClientManager::ClientManager()
{
    load();
}

ClientManager::~ClientManager()
{
    // 동적으로 할당된 Client 객체를 삭제
    for (auto& pair : mClientMap) {
        delete pair.second;
    }
    mClientMap.clear(); // 맵을 비우고, 모든 요소를 제거
}

ClientManager::ClientManager(const ClientManager& other)
{
    // 깊은 복사: 다른 객체의 클라이언트들에 대해 새로운 Client 객체를 생성
    for (const auto& pair : other.mClientMap) {
        // 클라이언트를 복사하여 새로운 메모리 공간에 저장
        mClientMap[pair.first] = new Client(*(pair.second));
    }
}

// 데이터 관리 
const bool ClientManager::add(const Client& client)
{
    Client* pClient = new Client(client.getId(), client.getName(), client.getPhoneNumber(), client.getPoint());
    
    pair<map<unsigned int, Client*>::iterator, bool> result = 
        mClientMap.insert(make_pair(client.getId(), pClient));
    if (result.second == false) { // 키 중복인 경우 실패
        delete pClient;
        return false;
    }

    appendToFile(client);

    return true;
}


const bool ClientManager::remove(const unsigned int id)
{
    auto it = mClientMap.find(id);
    if (it == mClientMap.end()) {
        return false;
    }

    delete it->second;    // 메모리 해제
    mClientMap.erase(it); // 클라이언트 삭제

    cout << "here" << endl;
    removeFromFile(id);   // 파일에서 클라이언트 제거
    cout << "here2" << endl;

    return true;
}

const Client* ClientManager::getByIdOrNull(const unsigned int id) const
{
    auto iter = mClientMap.find(id);
    if (iter == mClientMap.end()) {
        return nullptr;
    }

    return (iter->second);
}

// 저장소 관리
void ClientManager::load()
{
    ifstream fin;
    fin.open(ClientManagerConstants::RESOURCE);
    if(fin.fail() == true) {
        cerr << "[ClientManager] Fail: open file for reading" << endl;
        return ;
    }

    while(fin.eof() == false) {
        vector<string> row = parseCSV(fin, ',');
        if(row.size()) {
            unsigned int id = atoi(row[0].c_str());
            // string name = row[1];
            // string phoneNumber = row[2];
            int point = atoi(row[3].c_str());
            Client* client = new Client(id, row[1], row[2], point);
            mClientMap.insert(make_pair(id, client));
        }
    }
    
    fin.close( );
}

void clearConsole() {
    system("clear");
    // cout << "\033[2J\033[1;1H";
}

// View 관리
const bool ClientManager::displayMenu() 
{
    enum MenuOptions { DISPLAY_CLIENT_LIST = 1, INPUT_CLIENT, DELETE_CLIENT, QUIT_PROGRAM };

    // clearConsole();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Client Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Client List                     " << endl;
    cout << "  2. input Client                            " << endl;
    cout << "  3. Delete Client                           " << endl;
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

            cout << std::setw(45) << setfill('-') << "\n" << endl;
            cout << "Input Client (name)" << endl;
            cout << setw(45) << setfill('-') << "\n" << endl;
            inputItem();

            break;
        case DELETE_CLIENT:
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Delete Client" << endl;;
            cout << setw(45) << setfill('-') << "\n" << endl;

            displayItemsInfo();
            cout << "   Choose client id : ";

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



void ClientManager::displayItemsInfo() const
{
    cout << "Client list" << endl;
    cout << endl << "  ID  |     Name     " << endl;
    for (const auto& it : mClientMap) {
        Client* client = it.second;
        cout << setw(5) << setfill('0') << right << client->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << client->getName() << endl;
        cout << setw(12) << setfill(' ') << client->getPhoneNumber() << endl;
        cout << setw(12) << setfill(' ') << client->getPoint() << endl;
    }

    cout << endl;
    cout << "return to menu: enter any key" << endl;
}

void ClientManager::inputItem()
{
    string name;
    string phoneNumber;
    int point;
    cout << "name : "; cin >> name;
    cout << "phone number : "; cin >> phoneNumber;
    cout << "initial point : "; cin >> point;
    // validate field

    add(Client(generateId(), name, phoneNumber, point));
}

const unsigned int ClientManager::generateId() const
{

    // 로직의 수정이 필요할듯

    if (mClientMap.size() == 0) {
        return 0;
    } else {
        auto elem = mClientMap.end(); 
        int id = (--elem)->first;
        return ++id;
    }
}


vector<string> ClientManager::parseCSV(istream& fin, char delimiter)
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

void ClientManager::appendToFile(const Client& client) const
{
    ofstream fout;
    fout.open(ClientManagerConstants::RESOURCE, ios_base::app);
    if (fout.is_open() == false) {
        cerr << "[ClientManager] Fail: open file for writing" << endl;
        return; 
    }

    cout << client.toString() << endl;
    fout << client.toString() << endl;

    fout.close();
}

void ClientManager::removeFromFile(const unsigned int id) const
{
    ifstream fin;
    fin.open(ClientManagerConstants::RESOURCE);
    if (fin.is_open() == false) {
        cerr << "[ClientManager] Unable to open file for reading" << endl;
        return;
    }

    ofstream fout;
    fout.open(TEMP_BUFFER.c_str());  // 임시 파일을 쓰기 모드로 엽니다.
    if (fout.is_open() == false) {
        cerr << "[ClientManager] Unable to open temporary file for writing" << endl;
        fin.close();
        return;
    }


    string line;
    bool found = false;

    while (getline(fin, line)) {
        try {
            Client client = Client::createFromString(line);
            if (client.getId() == id) {
                found = true;
                // 제거할 클라이언트는 기록하지 않고 넘어갑니다.
                continue;
            }
            fout << line << endl;  // 제거할 클라이언트가 아니면 기록합니다.
        } catch (const invalid_argument&) {
            fout << line << endl;  // 클라이언트 생성에서 예외가 발생하면 기록합니다.
        }
    }

    fin.close();
    fout.close();

    if (found == true) {
        std::remove((ClientManagerConstants::RESOURCE).c_str());  // 원본 파일을 삭제합니다.
        rename(TEMP_BUFFER.c_str(), (ClientManagerConstants::RESOURCE).c_str());  // 임시 파일을 원본 파일 이름으로 변경합니다.
    } else {
        std::remove(TEMP_BUFFER.c_str());  // 제거할 클라이언트가 없으면 임시 파일을 삭제합니다.
    }
}
