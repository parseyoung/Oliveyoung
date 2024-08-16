#include"client.h"
#include"clientmanager.h"
#include "product.h"
#include"productmanager.h"
#include "Store.h"
#include "StoreManager.h"
#include<iostream>
using  namespace std;
int main()
{//초기화 리스트 혹은 리스트 초기화?
	ClientManager cm;
	ProductManager pm;
	StoreManager sm;
	Store s;
	int quit = 0;
	int ch = 0;
	while (quit != 1) {
		int ch;
		//cout << "\033[2J\033[1;1H";
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "          Welcome to Olive Yeong             " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "  1. Store Menu                              " << endl;
		cout << "  2. Product Manager                         " << endl;
		cout << "  3. Client Mangager                         " << endl;
		cout << "  4. Store Manager                           " << endl;
		cout << "  5. Quit this Program                       " << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << " What do you wanna do? ";
		cin >> ch;
		cin.ignore();
		switch (ch) {
		case 1: default:
			s.displayMenu();
			//cin#include"client.h"
#include"clientmanager.h"
#include "product.h"
#include"productmanager.h"
#include "Store.h"
#include "StoreManager.h"
#include<iostream>
			using  namespace std;
			int main()
			{//초기화 리스트 혹은 리스트 초기화?
				ClientManager cm;
				ProductManager pm;
				StoreManager sm;
				Store s;
				int quit = 0;
				int ch = 0;
				while (quit != 1) {
					int ch;
					//cout << "\033[2J\033[1;1H";
					cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
					cout << "          Welcome to Olive Yeong             " << endl;
					cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
					cout << "  1. Store Menu                              " << endl;
					cout << "  2. Product Manager                         " << endl;
					cout << "  3. Client Mangager                         " << endl;
					cout << "  4. Store Manager                           " << endl;
					cout << "  5. Quit this Program                       " << endl;
					cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
					cout << " What do you wanna do? ";
					cin >> ch;
					cin.ignore();
					switch (ch) {
					case 1: default:
						s.displayMenu();
						//cin.ignore();
						//getchar();
						break;
					case 2:
						pm.displayMenu();
						break;
					case 3:
						cm.displayMenu();
						break;
					case 4:
						sm.displayMenu();
						break;
					case 5:
						quit = 1;
						break;
					}

				}
			}.ignore();
			//getchar();
			break;
		case 2:
			pm.displayMenu();
			break;
		case 3:
			cm.displayMenu();
			break;
		case 4:
			sm.displayMenu();
			break;
		case 5:
			quit = 1;
			break;
		}

	}
}