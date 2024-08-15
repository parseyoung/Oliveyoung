#include "Clientmanager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

ClientManager::ClientManager() {
    loadClientsFromFile();
}

ClientManager::~ClientManager() {
    saveClientsToFile();
    for (const auto& clist : clientList) {
        delete clist.second;
    }
}

void ClientManager::loadClientsFromFile() {
    std::ifstream file("clients.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening clients.txt" << std::endl;
        return;
    }

    while (file.peek() != EOF) {
        std::vector<std::string> row = parseCSV(file, ',');
        if (row.size() == 3) {  
            try {
                int id = std::stoi(row[0]);
                Client* client = new Client(id, row[1], row[2]);
                clientList[id] = client;
            }
            catch (const std::invalid_argument&) {
                std::cerr << "Invalid data format in clients.txt" << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cerr << "ID value out of range in clients.txt" << std::endl;
            }
        }
        else if (!row.empty()) {
            std::cerr << "Incorrect data format in clients.txt" << std::endl;
        }
    }
    file.close();
}

void ClientManager::saveClientsToFile() {
    std::ofstream file("clients.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening clients.txt for saving data" << std::endl;
        return;
    }

    for (const auto& clist : clientList) {
        Client* client = clist.second;
        file << client->getId() << ',' << client->getName() << ','
             << client->getPhone() << std::endl;
    }
    file.close();
}

int ClientManager::makeId() {
    if (clientList.empty()) return 1;
    return clientList.rbegin()->first + 1;
}

std::vector<std::string> ClientManager::parseCSV(std::istream& file, char delimiter) {
    std::stringstream ss;
    std::vector<std::string> row;
    std::string t = " \n\r\t";

    while (file.peek() != EOF) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            std::string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}

void ClientManager::addClient(const string& name, const string phone) {
    int id = makeId();
    Client* client = new Client(id, name, phone);
    clientList[id] = client;
}

Client* ClientManager::searchClient(int id) {
    auto it = clientList.find(id);
    if (it != clientList.end()) {
        return it->second;
    }
    return nullptr;
}

void ClientManager::deleteClient(int id) {
    Client* client = searchClient(id);
    if (client) {
        delete client;
        clientList.erase(id);
        std::cout << "Client ID " << id << " deleted" << std::endl;
    }
    else {
        std::cerr << "Client ID " << id << " not found" << std::endl;
    }
}

void ClientManager::displayClient() {
    if (clientList.empty()) {
        std::cout << "No clients to display" << std::endl;
        return;
    }
    for (const auto& cli : clientList) {
        cli.second->displayInfo();
        std::cout << std::endl;
    }
}

bool ClientManager::displayMenu() {
    int choice, id;
    std::string name, address, phone;
    std::cout << std::endl;
    std::cout << "1. Display Client" << std::endl;
    std::cout << "2. Add Client" << std::endl;
    std::cout << "3. Delete Client" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cout << std::endl;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input, try again" << std::endl;
        return true;
    }

    switch (choice) {
    case 1:
        displayClient();
        break;

    case 2:
        std::cin.ignore();
        std::cout << "Enter name: "; std::getline(std::cin, name);
        std::cout << "Enter address: "; std::getline(std::cin, address);
        std::cout << "Enter phone: "; std::getline(std::cin, phone);
        addClient(name, phone);
        break;

    case 3:
        while (true) {
            std::cout << "Enter ID to delete: "; std::cin >> id;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid ID, try again" << std::endl;
            }
            else {
                deleteClient(id);
                break;
            }
        }
        break;

    case 4:
        return false;

    default:
        std::cerr << "Invalid choice. Try again." << std::endl;
        break;
    }
    return true;
}
