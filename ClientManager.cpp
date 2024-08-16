#include "Clientmanager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
// 생성자: ClientManager를 초기화하며 파일에서 클라이언트를 로드함
ClientManager::ClientManager() {
    loadClientsFromFile();
}

// 소멸자: 클라이언트를 파일에 저장하고 동적으로 할당된 메모리를 해제함
ClientManager::~ClientManager() {
    saveClientsToFile();
    // 동적 할당 된 clinet 객체 삭제 "map(id, Client*)"
    for (const auto& clist : mClientMap) {
        delete clist.second;
    }
}
// "clients.txt" 파일에서 클라이언트를 로드하는 함수
void ClientManager::loadClientsFromFile() {
    std::ifstream file("clients.txt");
    if (!file.is_open()) {
        cerr << "clients.txt 파일을 여는 중 오류 발생" << endl;
        return;
    }
    // 파일에서 각 줄을 읽고 CSV 형식으로 파싱
    while (file.peek() != EOF) {
        std::vector<std::string> row = parseCSV(file, ',');
        if (row.size() == 3) {  // 행에 3개의 요소(ID, 이름, 전화번호)
            try {
                int id = stoi(row[0]);
                Client* client = new Client(id, row[1], row[2]); // 새로운 client 객체 생성
                mClientMap[id] = client; // 맵에 client 객체 저장
            }
            catch (const invalid_argument&) {
                //std::cerr << "clients.txt에 잘못된 데이터 형식" << std::endl;
            }
            catch (const out_of_range&) {
                //std::cerr << "clients.txt에 ID 값이 범위를 초과함"  << std::endl;
            }
        }
        else if (!row.empty()) {
           // std::cerr << "clients.txt에 데이터 형식 오류" << std::endl;
        }
    }
    file.close();
}
// 현재 클라이언트 목록을 "clients.txt" 파일에 저장하는 함수
void ClientManager::saveClientsToFile() {
    std::ofstream file("clients.txt");
    if (!file.is_open()) {
        std::cerr << "clients.txt 파일에 데이터를 저장하는 중 오류 발생" << std::endl;
        return;
    }
    // 각 클라이언트의 데이터를 CSV 형식으로 파일에 작성
    for (const auto& clist : mClientMap) {
        Client* client = clist.second;
        file << client->getId() << ',' << client->getName() << ','
             << client->getPhone() << std::endl;
    }
    file.close();  // 파일 작성 완료 후 닫기
}

// 새로운 클라이언트에 대해 고유한 ID를 생성하는 함수
int ClientManager::makeId() {
    if (mClientMap.empty()) return 1;
    return mClientMap.rbegin()->first + 1; // // 맵의 가장 큰 키 값에 1을 더해 ID 생성
}

// CSV 파일의 한 줄을 구분자로 분리하는 함수
std::vector<std::string> ClientManager::parseCSV(std::istream& file, char delimiter) {
    std::stringstream ss;
    std::vector<std::string> row;
    std::string t = " \n\r\t"; // 각 필드의 앞뒤 공백을 제거하기 위한 문자들

    while (file.peek() != EOF) {
        char c = file.get(); // 파일에서 다음 문자를 가져옴
        if (c == delimiter || c == '\r' || c == '\n') { // 구분자나 줄바꿈을 만나면
            string s = ss.str(); // ss 생성
            s.erase(0, s.find_first_not_of(t)); // 앞의 공백 제거
            s.erase(s.find_last_not_of(t) + 1); // 뒤의 공백 제거
            row.push_back(s); // 필드를 행에 추가
            ss.str(""); // ss 초기화
            if (c != delimiter) break; // 줄의 끝이면 반복 종료
        }
        else {
            ss << c;  // 문자를 현재 필드에 추가
        }
    }
    return row; // parse된 행 반환
}

// 새로운 클라이언트를 추가하는 함수
void ClientManager::addClient(const string& name, const string phone) {
    int id = makeId();
    Client* client = new Client(id, name, phone);
    mClientMap[id] = client;
}

// ID로 클라이언트를 검색하는 함수
Client* ClientManager::searchClient(int id) {
    auto it = mClientMap.find(id);
    if (it != mClientMap.end()) { 
        return it->second; // 찾은 경우 Client 객체 반환
    }
    return nullptr;
}
// ID로 클라이언트를 삭제하는 함수
void ClientManager::deleteClient(int id) {
    Client* client = searchClient(id);
    if (client) {
        delete client; // client 객체 삭제
        mClientMap.erase(id); // map에서 해당 항목 제거
        cout << "고객 ID : " << id << " 삭제 완료" << endl;
    }
    else {
        cerr << "고객 ID : " << id << " 찾을 수 없음" << endl;
    }
}
// 모든 클라이언트를 출력하는 함수
void ClientManager::displayClient() {
    if (mClientMap.empty()) {
        cout << "고객을 찾을 수 없습니다." << endl;
        return;
    }
    for (const auto& client : mClientMap) {
        client.second->displayInfo(); // 각 Client 객체의 displayInfo() 호출
        cout << endl;
    }
}
// 사용자 메뉴 함수
bool ClientManager::displayMenu() {
    int choice, id;
    string name, address, phone;

    // 메뉴 UI 시작
    cout << "\n===================================" << endl;
    cout << "         고객 관리 시스템          " << endl;
    cout << "===================================" << endl;

    // 메뉴 옵션 출력
    cout << "| 1. 고객 정보 확인               |" << endl;
    cout << "| 2. 신규 고객 추가               |" << endl;
    cout << "| 3. 고객 정보 삭제               |" << endl;
    cout << "| 4. 종료                         |" << endl;
    cout << "===================================" << endl;

    cout << " 선택을 입력하세요: ";
    cin >> choice;
    cout << "===================================" << endl;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << " 잘못된 입력입니다. 다시 시도하세요" << endl;
        return true;
    }

    switch (choice) {
    case 1:
        cout << "\n****** 고객 정보 확인 ******" << endl;
        displayClient();
        cout << "****************************" << endl;
        break;

    case 2:
        cin.ignore();
        cout << "\n****** 신규 고객 추가 ******" << endl;
        cout << " 이름을 입력하세요: "; getline(cin, name);
        cout << " 주소를 입력하세요: "; getline(cin, address);
        cout << " 전화번호를 입력하세요: "; getline(cin, phone);
        addClient(name, phone);
        cout << " 고객이 성공적으로 추가되었습니다!" << endl;
        cout << "****************************" << endl;
        break;

    case 3:
        cout << "\n****** 고객 정보 삭제 ******" << endl;
        while (true) {
            cout << " 삭제할 고객의 ID를 입력하세요: "; cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << " 잘못된 ID입니다. 다시 시도하세요" << endl;
            }
            else {
                deleteClient(id);
                cout << " 고객이 성공적으로 삭제되었습니다!" << endl;
                break;
            }
        }
        cout << "****************************" << endl;
        break;

    case 4:
        cout << " 시스템을 종료합니다." << endl;
        cout << "===================================" << endl;
        return false;

    default:
        cerr << " 잘못된 선택입니다. 다시 시도하세요." << endl;
        cout << "===================================" << endl;
        break;
    }

    return true;
}

