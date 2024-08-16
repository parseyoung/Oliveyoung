#include "ProductManager.h"
#include "Product.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

/* ProductManager Ŭ������ ������
 CategoryManager��ü�� ������ �ް�, ��������� �ʱ�ȭ*/
ProductManager::ProductManager(CategoryManager& categoryManager) 
    : mCategoryManager(categoryManager){
    loadProductsFromFile(); // ���α׷��� ���� �� ���� �ε�
}

// ProductManager Ŭ������ �Ҹ���
ProductManager::~ProductManager() {
    saveProductsToFile(); // ��ǰ ������ ���Ͽ� ����
    for (const auto& plist : mProductMap) { 
        delete plist.second; // ��ǰ ��ü �޸� ����
    }
}

void ProductManager::loadProductsFromFile() {
    std::ifstream file("products.txt");
    if (!file.is_open()) {
        cerr << "products.txt ���� ���� ����" << endl;
        return;
    }

    while (file.peek() != EOF) {
        std::vector<std::string> row = parseCSV(file, ',');
        if (row.size() == 5) { // (id, ī�װ�, �̸�, ����, ����)
            try {
                int id = std::stoi(row[0]);
                string category = row[1];
                string name = row[2];
                int price = std::stoi(row[3]);
                int quantity = std::stoi(row[4]);

                Product* product = new Product(id, category, name, price, quantity);
                mProductMap[id] = product;

                //  CategoryManager���� �ش� ī�װ� ã�Ƽ� ��ǰ�� ī�װ��� �߰�
                Category* cat = mCategoryManager.getCategory(category);
                if (cat) {
                    cat->addProduct(product);
                }
                else {
                    std::cerr << "ī�װ� " << category << " �� ã�� �� �����ϴ�. ��ǰ : " << row[1] << std::endl;
                }
            }
            catch (const std::invalid_argument&) {
                //std::cerr << "products.txt���� �߸��� ������ ����" << std::endl;
            }
            catch (const std::out_of_range&) {
                //std::cerr << "products.txt���� ������ ��� �� << std::endl;
            }
        }
        else if (!row.empty()) {
            //std::cerr << "products.txt���� �߸��� ������ ����" << std::endl;
        }
    }
    file.close();
}

// ��ǰ �����͸� ���Ͽ� �����ϴ� �Լ�
void ProductManager::saveProductsToFile() {
    std::ofstream file("products.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening products.txt for saving data" << std::endl;
        return;
    }

    for (const auto& plist : mProductMap) {
        Product* product = plist.second;
        file << product->getId() << ',' << product->getCategory() << ',' << product->getName() << ','
            << product->getPrice() << ',' << product->getQuantity() << std::endl;
    }
    file.close();
}

// CSV ������ �����͸� �Ľ��ϴ� �Լ�
std::vector<std::string> ProductManager::parseCSV(std::istream& file, char delimiter) {
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
// ���ο� ��ǰ ID�� �����ϴ� �Լ�
int ProductManager::makeId() {
    if (mProductMap.empty()) return 1;
    return mProductMap.rbegin()->first + 1;
}

void ProductManager::addProduct(const string& categoryName, const string& name, int price, int quantity) {
    // [mProductList] first : id, second : product*
    for (auto& pair : mProductMap) {
        Product* product = pair.second;
        // ���� ��ǰ�� ��� ���� ����
        if (product->getName() == name && product->getPrice() == price) {
            product->setQuantity(product->getQuantity() + quantity);
            cout << "Product updated: " << name << endl;
            return;
        }
    }
    int id = makeId();
    // ���ο� ��ǰ ��ü ����
    Product* product = new Product(id, categoryName, name, price, quantity);
    // mProductList�� ��ü �߰�
    mProductMap[id] = product;

    // ī�װ� Ȯ�� �� �߰�
    Category* category = mCategoryManager.getCategory(categoryName);
    if (category) {
        category->addProduct(product);
    }
    else {
        cout << "�ش� ī�װ��� �������� �ʽ��ϴ�. ī�װ��� �߰��Ͻðڽ��ϱ�? (Y/N) : ";
        char respones;
        cin >> respones;
        if (respones == 'y' || respones == 'Y') {
            mCategoryManager.addCategory(categoryName);
            Category* newCategory = mCategoryManager.getCategory(categoryName);
            if (newCategory) {
                newCategory->addProduct(product); // �� ī�װ��� ��ǰ�� �߰�
            }
        }
        else {
            delete product;
            cout << "��ǰ�� �߰����� �ʾҽ��ϴ�. ī�װ��� �߰����ּ���." << endl;
        }
    }

    std::cout << "��ǰ�� �߰��Ǿ����ϴ�: " << name << endl;
}
// ��ǰ ID�� ��ǰ�� �˻��ϴ� �Լ�
Product* ProductManager::searchProduct(int id) const{
    auto it = mProductMap.find(id);

    // ��ǰ�� �����ϴ� ���
    if (it != mProductMap.end()) {
        return it->second;
    }
    return nullptr;
}

// �־��� ID�� ���� ��ǰ�� �����ϴ� �Լ�
void ProductManager::deleteProduct(int id) {
    Product* product = searchProduct(id);
    if (product) {
        // ��ǰ�� ī�װ��� ������
        Category* category = mCategoryManager.getCategory(product->getCategory());
        if (category) {
            // ī�װ������� ��ǰ�� ����
            category->deleteProduct(id);
        }
        delete product; // ��ǰ ��ü ����
        mProductMap.erase(id);
        cout << "��ǰ ID :" << id << " �����Ǿ����ϴ�. " << endl;
    }
    else {
        cerr << "��ǰ ID : " << id << " ã�� �� �����ϴ�." << endl;
    }
}
// ��� ��ǰ�� ������ ����ϴ� �Լ�
void ProductManager::displayProducts() const{
    if (mProductMap.empty()) {
        cout << "��ǰ�� �������� �ʽ��ϴ�. " << endl;
        return;
    }
    for (const auto& product : mProductMap) {
        product.second->displayInfo(); // ��ǰ ��ü�� ���� ���
    }
}

// ����� �޴� ǥ�� �Լ�
bool ProductManager::displayMenu() {
    int choice, id;
    string categoryName, name;
    int price;
    int quantity;

    // �޴� UI ����
    cout << "\n===================================" << endl;
    cout << "         ��ǰ ���� �ý���          " << endl;
    cout << "===================================" << endl;

    // �޴� �ɼ� ���
    cout << "| 1. ��ǰ ��� ����               |" << endl;
    cout << "| 2. ��ǰ �߰�                    |" << endl;
    cout << "| 3. ��ǰ ����                    |" << endl;
    cout << "| 4. ����                         |" << endl;
    cout << "===================================" << endl;

    cout << " ������ �Է��ϼ���: ";
    cin >> choice;
    cout << "===================================" << endl;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << " �߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        return true;
    }

    switch (choice) {
    case 1:
        cout << "\n****** ��ǰ ��� ���� ******" << endl;
        displayProducts();
        cout << "****************************" << endl;
        break;

    case 2:
        cin.ignore();
        cout << "\n****** ��ǰ �߰� ******" << endl;
        cout << " ��ǰ �̸��� �Է��ϼ���: "; getline(cin, name);
        cout << " ��ǰ ������ �Է��ϼ���: "; cin >> price;
        cout << " ��ǰ ������ �Է��ϼ���: "; cin >> quantity;
        cin.ignore();
        cout << " ��ǰ ī�װ��� �Է��ϼ���: "; getline(cin, categoryName);
        addProduct(categoryName, name, price, quantity);
        cout << " ��ǰ�� ���������� �߰��Ǿ����ϴ�!" << endl;
        cout << "****************************" << endl;
        break;

    case 3:
        cout << "\n****** ��ǰ ���� ******" << endl;
        while (true) {
            cout << " ������ ��ǰ�� ID�� �Է��ϼ���: "; cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << " �߸��� ID�Դϴ�. �ٽ� �õ��ϼ���." << endl;
            }
            else {
                deleteProduct(id);
                break;
            }
        }
        cout << "****************************" << endl;
        break;

    case 4:
        return false;

    default:
        cerr << " �߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl;
        break;
    }
    return true;
}
