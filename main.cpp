#include "ClientManager.h"
#include "ProductManager.h"
#include "CategoryManager.h"
#include "Store.h"
#include <iostream>
#include <limits> 

using namespace std;

void displayRoleMenu();
void handleClientActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store);
void handleManagerActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store);
int getValidatedInput();

int main() {
    ClientManager clientManager;
    CategoryManager categoryManager;
    ProductManager productManager(categoryManager);
    Store store(clientManager, productManager, categoryManager);

    bool running = true;

    while (running) {
        displayRoleMenu();
        int roleChoice = getValidatedInput();

        switch (roleChoice) {
        case 1: // Customer
            handleClientActions(clientManager, productManager, categoryManager, store);
            break;
        case 2: // Manager
            handleManagerActions(clientManager, productManager, categoryManager, store);
            break;
        case 3: // Exit
            running = false;
            break;
        default:
            cerr << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
    }

    return 0;
}

void displayRoleMenu() {
    cout << "\nMenu:\n";
    cout << "1. 고객\n";
    cout << "2. 관리자\n";
    cout << "3. 종료\n";
    cout << "선택해주세요: ";
}

int getValidatedInput() {
    int input;
    while (!(cin >> input)) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cerr << "잘못된 입력입니다. 숫자를 입력해주세요: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard any remaining input
    return input;
}

void handleClientActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store) {
    int choice;
    cout << "\n고객 메뉴:\n";
    cout << "1. 카테고리별 제품 보기\n";
    cout << "2. 모든 제품 보기\n";
    cout << "3. 카테고리 보기\n";
    cout << "4. 상품 구매\n";
    cout << "5. 메인 메뉴로 돌아가기\n";
    cout << "선택해주세요: ";
    choice = getValidatedInput();

    cin.ignore();

    switch (choice) {
    case 1: {
        string categoryName;
        cout << "카테고리 이름을 입력해주세요: ";
        getline(cin, categoryName);
        Category* category = categoryManager.getCategory(categoryName);
        if (category) {
            category->displayProducts();
        }
        else {
            cerr << "카테고리를 찾을 수 없습니다." << endl;
        }
        break;
    }
    case 2:
        productManager.displayProducts();
        break;
    case 3:
        categoryManager.displayCategories();
        break;
    case 4: {
        int clientId, productId;
        cout << "고객 ID를 입력해주세요: ";
        clientId = getValidatedInput();
        cout << "구매할 상품 ID를 입력해주세요: ";
        productId = getValidatedInput();
        store.sellProduct(clientId, productId);
        break;
    }
    case 5:
        break;
    default:
        cerr << "잘못된 선택입니다. 다시 시도해주세요." << endl;
        break;
    }
}

void handleManagerActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store) {
    int choice;
    cout << "\n관리자 메뉴:\n";
    cout << "1. 고객 관리\n";
    cout << "2. 제품 관리\n";
    cout << "3. 카테고리 관리\n";
    cout << "4. 재고 관리\n";
    cout << "5. 판매 내역 보기\n";
    cout << "6. 메인 메뉴로 돌아가기\n";
    cout << "선택해주세요: ";
    choice = getValidatedInput();

    cin.ignore();

    switch (choice) {
    case 1:
        // 고객 관리
        int clientChoice;
        cout << "\n고객 관리 메뉴:\n";
        cout << "1. 고객 추가\n";
        cout << "2. 고객 삭제\n";
        cout << "3. 고객 목록 보기\n";
        cout << "4. 관리자 메뉴로 돌아가기\n";
        cout << "선택해주세요: ";
        clientChoice = getValidatedInput();

        switch (clientChoice) {
        case 1: {
            string name, phone;
            cout << "고객 이름을 입력해주세요: ";
            getline(cin, name);
            cout << "고객 전화번호를 입력해주세요: ";
            getline(cin, phone);
            clientManager.addClient(name, phone);
            break;
        }
        case 2: {
            int id;
            cout << "삭제할 고객 ID를 입력해주세요: ";
            id = getValidatedInput();
            clientManager.deleteClient(id);
            break;
        }
        case 3:
            clientManager.displayClient();
            break;
        case 4:
            break;
        default:
            cerr << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
        break;

    case 2:
        // 제품 관리
        int productChoice;
        cout << "\n제품 관리 메뉴:\n";
        cout << "1. 제품 추가\n";
        cout << "2. 제품 삭제\n";
        cout << "3. 제품 목록 보기\n";
        cout << "4. 관리자 메뉴로 돌아가기\n";
        cout << "선택해주세요: ";
        productChoice = getValidatedInput();

        cin.ignore();

        switch (productChoice) {
        case 1: {
            string categoryName, name;
            int price, quantity;
            cout << "제품 이름을 입력해주세요: ";
            getline(cin, name);
            cout << "제품 가격을 입력해주세요: ";
            price = getValidatedInput();
            cout << "제품 수량을 입력해주세요: ";
            quantity = getValidatedInput();
            cin.ignore();
            cout << "카테고리 이름을 입력해주세요: ";
            getline(cin, categoryName);
            productManager.addProduct(categoryName, name, price, quantity);
            break;
        }
        case 2: {
            int id;
            cout << "삭제할 상품 ID를 입력해주세요: ";
            id = getValidatedInput();
            productManager.deleteProduct(id);
            break;
        }
        case 3:
            productManager.displayProducts();
            break;
        case 4:
            break;
        default:
            cerr << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
        break;

    case 3:
        // 카테고리 관리
        int categoryChoice;
        cout << "\n카테고리 관리 메뉴:\n";
        cout << "1. 카테고리 추가\n";
        cout << "2. 카테고리 삭제\n";
        cout << "3. 카테고리 목록 보기\n";
        cout << "4. 관리자 메뉴로 돌아가기\n";
        cout << "선택해주세요: ";
        categoryChoice = getValidatedInput();

        cin.ignore();

        switch (categoryChoice) {
        case 1: {
            string name;
            cout << "카테고리 이름을 입력해주세요: ";
            getline(cin, name);
            categoryManager.addCategory(name);
            break;
        }
        case 2: {
            string name;
            cout << "삭제할 카테고리 이름을 입력해주세요: ";
            getline(cin, name);
            categoryManager.deleteCategory(name);
            break;
        }
        case 3:
            categoryManager.displayCategories();
            break;
        case 4:
            break;
        default:
            cerr << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
        break;

    case 4: {
        // 재고 관리
        int productId, stock;
        cout << "재고를 수정할 상품 ID를 입력해주세요: ";
        productId = getValidatedInput();
        cout << "새로운 재고 수량을 입력해주세요: ";
        stock = getValidatedInput();
        store.updateStock(productId, stock);
        break;
    }

    case 5:
        // 판매 내역 보기
        store.displayPurchaseHistory();
        break;

    case 6:
        break;

    default:
        cerr << "잘못된 선택입니다. 다시 시도해주세요." << endl;
        break;
    }
}
