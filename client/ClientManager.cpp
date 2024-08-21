#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <regex>
#include "ClientManager.h"
#include "Client.h"
#include "../Validation/Validation.h"

using namespace std;

// ClientManager 클래스의 생성자: 클라이언트 데이터를 로드
ClientManager::ClientManager()
{
    load();
}

// ClientManager 클래스의 소멸자: 동적으로 할당된 Client 객체들을 삭제
ClientManager::~ClientManager()
{
    for (auto& pair : mClientMap) {
        delete pair.second;
    }
    mClientMap.clear(); // 맵을 비우고, 모든 요소를 제거
}

// ClientManager 클래스의 복사 생성자: 깊은 복사 
ClientManager::ClientManager(const ClientManager& other)
{
    // 다른 ClientManager 객체의 클라이언트 맵을 깊은 복사하여 새로운 Client 객체를 생성
    for (const auto& pair : other.mClientMap) {
        // 클라이언트를 복사하여 새로운 메모리 공간에 저장
        mClientMap[pair.first] = new Client(*(pair.second));
    }
}

// 클라이언트를 추가하는 함수
bool ClientManager::add(const Client& client)
{
    return BaseEntity<Client>::add(client);

}

// 클라이언트를 제거하는 함수
bool ClientManager::remove(const unsigned int id)
{
    return BaseEntity<Client>::remove(id);  // BaseEntity의 remove 메소드 호출


}

// ID로 클라이언트를 검색하여 포인터를 반환하는 함수 (없으면 nullptr 반환)
const Client* ClientManager::getByIdOrNull(const unsigned int id) const
{
    auto iter = mClientMap.find(id);
    if (iter == mClientMap.end()) {
        return nullptr;
    }

    return (iter->second);
}

// 클라이언트 데이터를 파일에서 로드하는 함수
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
            int point = atoi(row[3].c_str());
            Client* client = new Client(id, row[1], row[2], point);
            mClientMap.insert(make_pair(id, client));
        }
    }
    
    fin.close( );
}

// 콘솔을 지우는 함수 (추가적인 기능으로 clear 명령을 사용)
void clearConsole() {
    system("clear");
}


// 메뉴를 표시하고 사용자 입력을 받는 함수
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
            // 클라이언트 목록 표시
            // clearConsole();

            displayItemsInfo();
            cin.ignore();
            getchar();

            break;
        case INPUT_CLIENT:
            // 클라이언트 입력
            // clearConsole();

            cout << setw(45) << setfill('-') << "\n" << endl;
            cout << "Input Client (name)" << endl;
            cout << setw(45) << setfill('-') << "\n" << endl;
            inputItem();

            break;
        case DELETE_CLIENT:
            // 클라이언트 삭제
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


// 클라이언트 목록을 표시하는 함수
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


// 사용자로부터 클라이언트 정보를 입력받아 Client를 추가
void ClientManager::inputItem() {
    string name;
    string phoneNumber;
    int points;

    // 클라이언트 이름 유효성 검사
    while (true) {
        cout << "name : "; cin >> name;
        if (Validation::validateClientName(name)) {
            break;
        }
    }

    // 전화번호 유효성 검사
    while (true) {
        cout << "phone number : "; cin >> phoneNumber;
        if (Validation::validateClientPhoneNumber(phoneNumber)) {
            break;
        }
    }

    // 포인트 유효성 검사
    while (true) {
        cout << "initial point : "; cin >> points;
        if (cin.fail()) {
            cin.clear(); // 입력 스트림을 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력을 무시
            cout << "Error: Points must be a non-negative integer." << endl;
        }
        else if (Validation::validateClientPoints(points)) {
            break;
        }
    }

    // Client를 추가
    add(Client(generateId(), name, phoneNumber, points));
}

unsigned int ClientManager::generateId() const
{
    return BaseEntity<Client>::generateId(mClientMap);
}

// CSV 파일을 파싱하여 데이터를 벡터로 반환하는 함수
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

// 클라이언트 정보를 파일에 추가하는 함수
void ClientManager::appendToFile(const Client& client) const
{
    ofstream fout;
    fout.open(ClientManagerConstants::RESOURCE, ios_base::app);
    if (fout.is_open() == false) {
        cerr << "[ClientManager] Fail: open file for writing" << endl;
        return; 
    }

    cout << client.toString() << endl;
    // 클라이언트 정보를 파일에 추가
    fout << client.toString() << endl;

    fout.close();
}

// 파일에서 특정 ID의 클라이언트를 제거하는 함수
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
