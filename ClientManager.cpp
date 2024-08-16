#include "Clientmanager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
// ������: ClientManager�� �ʱ�ȭ�ϸ� ���Ͽ��� Ŭ���̾�Ʈ�� �ε���
ClientManager::ClientManager() {
    loadClientsFromFile();
}

// �Ҹ���: Ŭ���̾�Ʈ�� ���Ͽ� �����ϰ� �������� �Ҵ�� �޸𸮸� ������
ClientManager::~ClientManager() {
    saveClientsToFile();
    // ���� �Ҵ� �� clinet ��ü ���� "map(id, Client*)"
    for (const auto& clist : mClientMap) {
        delete clist.second;
    }
}
// "clients.txt" ���Ͽ��� Ŭ���̾�Ʈ�� �ε��ϴ� �Լ�
void ClientManager::loadClientsFromFile() {
    std::ifstream file("clients.txt");
    if (!file.is_open()) {
        cerr << "clients.txt ������ ���� �� ���� �߻�" << endl;
        return;
    }
    // ���Ͽ��� �� ���� �а� CSV �������� �Ľ�
    while (file.peek() != EOF) {
        std::vector<std::string> row = parseCSV(file, ',');
        if (row.size() == 3) {  // �࿡ 3���� ���(ID, �̸�, ��ȭ��ȣ)
            try {
                int id = stoi(row[0]);
                Client* client = new Client(id, row[1], row[2]); // ���ο� client ��ü ����
                mClientMap[id] = client; // �ʿ� client ��ü ����
            }
            catch (const invalid_argument&) {
                //std::cerr << "clients.txt�� �߸��� ������ ����" << std::endl;
            }
            catch (const out_of_range&) {
                //std::cerr << "clients.txt�� ID ���� ������ �ʰ���"  << std::endl;
            }
        }
        else if (!row.empty()) {
           // std::cerr << "clients.txt�� ������ ���� ����" << std::endl;
        }
    }
    file.close();
}
// ���� Ŭ���̾�Ʈ ����� "clients.txt" ���Ͽ� �����ϴ� �Լ�
void ClientManager::saveClientsToFile() {
    std::ofstream file("clients.txt");
    if (!file.is_open()) {
        std::cerr << "clients.txt ���Ͽ� �����͸� �����ϴ� �� ���� �߻�" << std::endl;
        return;
    }
    // �� Ŭ���̾�Ʈ�� �����͸� CSV �������� ���Ͽ� �ۼ�
    for (const auto& clist : mClientMap) {
        Client* client = clist.second;
        file << client->getId() << ',' << client->getName() << ','
             << client->getPhone() << std::endl;
    }
    file.close();  // ���� �ۼ� �Ϸ� �� �ݱ�
}

// ���ο� Ŭ���̾�Ʈ�� ���� ������ ID�� �����ϴ� �Լ�
int ClientManager::makeId() {
    if (mClientMap.empty()) return 1;
    return mClientMap.rbegin()->first + 1; // // ���� ���� ū Ű ���� 1�� ���� ID ����
}

// CSV ������ �� ���� �����ڷ� �и��ϴ� �Լ�
std::vector<std::string> ClientManager::parseCSV(std::istream& file, char delimiter) {
    std::stringstream ss;
    std::vector<std::string> row;
    std::string t = " \n\r\t"; // �� �ʵ��� �յ� ������ �����ϱ� ���� ���ڵ�

    while (file.peek() != EOF) {
        char c = file.get(); // ���Ͽ��� ���� ���ڸ� ������
        if (c == delimiter || c == '\r' || c == '\n') { // �����ڳ� �ٹٲ��� ������
            string s = ss.str(); // ss ����
            s.erase(0, s.find_first_not_of(t)); // ���� ���� ����
            s.erase(s.find_last_not_of(t) + 1); // ���� ���� ����
            row.push_back(s); // �ʵ带 �࿡ �߰�
            ss.str(""); // ss �ʱ�ȭ
            if (c != delimiter) break; // ���� ���̸� �ݺ� ����
        }
        else {
            ss << c;  // ���ڸ� ���� �ʵ忡 �߰�
        }
    }
    return row; // parse�� �� ��ȯ
}

// ���ο� Ŭ���̾�Ʈ�� �߰��ϴ� �Լ�
void ClientManager::addClient(const string& name, const string phone) {
    int id = makeId();
    Client* client = new Client(id, name, phone);
    mClientMap[id] = client;
}

// ID�� Ŭ���̾�Ʈ�� �˻��ϴ� �Լ�
Client* ClientManager::searchClient(int id) {
    auto it = mClientMap.find(id);
    if (it != mClientMap.end()) { 
        return it->second; // ã�� ��� Client ��ü ��ȯ
    }
    return nullptr;
}
// ID�� Ŭ���̾�Ʈ�� �����ϴ� �Լ�
void ClientManager::deleteClient(int id) {
    Client* client = searchClient(id);
    if (client) {
        delete client; // client ��ü ����
        mClientMap.erase(id); // map���� �ش� �׸� ����
        cout << "�� ID : " << id << " ���� �Ϸ�" << endl;
    }
    else {
        cerr << "�� ID : " << id << " ã�� �� ����" << endl;
    }
}
// ��� Ŭ���̾�Ʈ�� ����ϴ� �Լ�
void ClientManager::displayClient() {
    if (mClientMap.empty()) {
        cout << "���� ã�� �� �����ϴ�." << endl;
        return;
    }
    for (const auto& client : mClientMap) {
        client.second->displayInfo(); // �� Client ��ü�� displayInfo() ȣ��
        cout << endl;
    }
}
// ����� �޴� �Լ�
bool ClientManager::displayMenu() {
    int choice, id;
    string name, address, phone;

    // �޴� UI ����
    cout << "\n===================================" << endl;
    cout << "         �� ���� �ý���          " << endl;
    cout << "===================================" << endl;

    // �޴� �ɼ� ���
    cout << "| 1. �� ���� Ȯ��               |" << endl;
    cout << "| 2. �ű� �� �߰�               |" << endl;
    cout << "| 3. �� ���� ����               |" << endl;
    cout << "| 4. ����                         |" << endl;
    cout << "===================================" << endl;

    cout << " ������ �Է��ϼ���: ";
    cin >> choice;
    cout << "===================================" << endl;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << " �߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���" << endl;
        return true;
    }

    switch (choice) {
    case 1:
        cout << "\n****** �� ���� Ȯ�� ******" << endl;
        displayClient();
        cout << "****************************" << endl;
        break;

    case 2:
        cin.ignore();
        cout << "\n****** �ű� �� �߰� ******" << endl;
        cout << " �̸��� �Է��ϼ���: "; getline(cin, name);
        cout << " �ּҸ� �Է��ϼ���: "; getline(cin, address);
        cout << " ��ȭ��ȣ�� �Է��ϼ���: "; getline(cin, phone);
        addClient(name, phone);
        cout << " ���� ���������� �߰��Ǿ����ϴ�!" << endl;
        cout << "****************************" << endl;
        break;

    case 3:
        cout << "\n****** �� ���� ���� ******" << endl;
        while (true) {
            cout << " ������ ���� ID�� �Է��ϼ���: "; cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << " �߸��� ID�Դϴ�. �ٽ� �õ��ϼ���" << endl;
            }
            else {
                deleteClient(id);
                cout << " ���� ���������� �����Ǿ����ϴ�!" << endl;
                break;
            }
        }
        cout << "****************************" << endl;
        break;

    case 4:
        cout << " �ý����� �����մϴ�." << endl;
        cout << "===================================" << endl;
        return false;

    default:
        cerr << " �߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl;
        cout << "===================================" << endl;
        break;
    }

    return true;
}

