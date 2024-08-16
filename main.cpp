#include "ClientManager.h"
#include "ProductManager.h"
#include "CategoryManager.h"
#include "Store.h"
#include <iostream>
#include <limits>

using namespace std;

// 전방선언
void displayRoleMenu();
void handleClientActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store);
void handleManagerActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store);
int getValidatedInput();

int main() {
    // 객체 생성
    ClientManager clientManager;
    CategoryManager categoryManager;
    ProductManager productManager(categoryManager);
    Store store(clientManager, productManager, categoryManager);

    bool running = true;

    while (running) {
        displayRoleMenu();
        int roleChoice = getValidatedInput();

        switch (roleChoice) {
        case 1: // 고객
            handleClientActions(clientManager, productManager, categoryManager, store);
            break;
        case 2: // 관리자
            handleManagerActions(clientManager, productManager, categoryManager, store);
            break;
        case 3: // 종료
            running = false;
            break;
        default:
            cerr << "\n[오류] 잘못된 선택입니다. 다시 시도해 주세요." << endl;
            break;
        }
    }

    return 0;
}
// 역할 선택 메뉴를 출력하는 함수
void displayRoleMenu() {
    cout << "\n==============================\n";
    cout << "          메인 메뉴\n";
    cout << "==============================\n";
    cout << "1. 고객\n";
    cout << "2. 관리자\n";
    cout << "3. 종료\n";
    cout << "==============================\n";
    cout << "선택해주세요: ";
}
// 유효한 정수를 입력받는 함수
int getValidatedInput() {
    int input;
    while (!(cin >> input)) {
        cin.clear(); // 오류 플래그 지우기
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력 무시하기
        cerr << "[오류] 잘못된 입력입니다. 숫자를 입력해주세요: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 남은 입력 무시하기
    return input;
}

// 고객 관련 작업을 처리하는 함수
void handleClientActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store) {
    int choice;
    cout << "\n==============================\n";
    cout << "        고객 메뉴\n";
    cout << "==============================\n";
    cout << "1. 카테고리별 제품 보기\n";
    cout << "2. 모든 제품 보기\n";
    cout << "3. 카테고리 보기\n";
    cout << "4. 상품 구매\n";
    cout << "5. 메인 메뉴로 돌아가기\n";
    cout << "==============================\n";
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
            cerr << "[오류] 카테고리를 찾을 수 없습니다." << endl;
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
        store.sellProduct(clientId, productId); // 제품 구매 처리
        break;
    }
    case 5:
        break;
    default:
        cerr << "[오류] 잘못된 선택입니다. 다시 시도해 주세요." << endl;
        break;
    }
}
// 고객 관련 작업을 처리하는 함수
void handleManagerActions(ClientManager& clientManager, ProductManager& productManager, CategoryManager& categoryManager, Store& store) {
    int choice;
    cout << "\n==============================\n";
    cout << "        관리자 메뉴\n";
    cout << "==============================\n";
    cout << "1. 고객 관리\n";
    cout << "2. 제품 관리\n";
    cout << "3. 카테고리 관리\n";
    cout << "4. 재고 관리\n";
    cout << "5. 판매 내역 보기\n";
    cout << "6. 메인 메뉴로 돌아가기\n";
    cout << "==============================\n";
    cout << "선택해주세요: ";
    choice = getValidatedInput();

    cin.ignore();

    switch (choice) {
    case 1:
        // 고객 관리
        int clientChoice;
        cout << "\n==============================\n";
        cout << "    고객 관리 메뉴\n";
        cout << "==============================\n";
        cout << "1. 고객 추가\n";
        cout << "2. 고객 삭제\n";
        cout << "3. 고객 목록 보기\n";
        cout << "4. 관리자 메뉴로 돌아가기\n";
        cout << "==============================\n";
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
            cerr << "[오류] 잘못된 선택입니다. 다시 시도해 주세요." << endl;
            break;
        }
        break;

    case 2:
        // 제품 관리
        int productChoice;
        cout << "\n==============================\n";
        cout << "    제품 관리 메뉴\n";
        cout << "==============================\n";
        cout << "1. 제품 추가\n";
        cout << "2. 제품 삭제\n";
        cout << "3. 제품 목록 보기\n";
        cout << "4. 관리자 메뉴로 돌아가기\n";
        cout << "==============================\n";
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
            cerr << "[오류] 잘못된 선택입니다. 다시 시도해 주세요." << endl;
            break;
        }
        break;

    case 3:
        // 카테고리 관리
        int categoryChoice;
        cout << "\n==============================\n";
        cout << "    카테고리 관리 메뉴\n";
        cout << "==============================\n";
        cout << "1. 카테고리 추가\n";
        cout << "2. 카테고리 삭제\n";
        cout << "3. 카테고리 목록 보기\n";
        cout << "4. 관리자 메뉴로 돌아가기\n";
        cout << "==============================\n";
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
            cerr << "[오류] 잘못된 선택입니다. 다시 시도해 주세요." << endl;
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
        cerr << "[오류] 잘못된 선택입니다. 다시 시도해 주세요." << endl;
        break;
    }
}
