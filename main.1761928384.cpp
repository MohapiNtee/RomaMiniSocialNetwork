#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "class_1.h"
#include "Functions.h"

int main(){
    loadLoginData();
    int choice;
	
    do {
        cout << "\n===== Roma Mini Social Network =====\n";
        cout << "1. Login"<<endl;
        cout << "2. Register"<<endl;
        cout << "3. Exit\n"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        	loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
