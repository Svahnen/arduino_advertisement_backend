#include <iostream>
#include "advertisment.hpp"

using namespace std;

static int addAd() {
    int sum;
    string adText;

    cout << "Enter sum :";
    cin >> sum;
    cout << "Enter text: ";
    cin >> adText;

    cout << "You have added an ad" << endl;
    return 0;
}

static int viewAd() {
    cout << "You have viewed an ad" << endl;
    return 0;
}

static int deleteAd() {
    cout << "You have deleted an ad" << endl;
    return 0;
}

static int showMenu() {
    int choice;
    cout << "1. Add advertisment" << endl;
    cout << "2. View advertisment" << endl;
    cout << "3. Delete advertisment" << endl;
    cout << "0. Quit program" << endl;
    cout << "Enter menu choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        addAd();
        break;
    case 2:
        viewAd();
        break;
    case 3:
        deleteAd();
        break;
    case 0:
        cout << "You have quitted the program" << endl;
        exit(EXIT_SUCCESS);
    default:
        cout << "Please enter a correct choice!" << endl;
        break;
    }
    return 0;
}

int main(int argc, char** argv) {
    cout << "Have " << argc -1 << " arguments:" << endl;
    for (int i = 1; i < argc; ++i) {
        cout << argv[i] << endl;
    }
    
    Advertisments Arduino;
    Arduino.setAd(500, "Sell your car today!");

    cout << "Sum: " << Arduino.getadSum() << endl;
    cout << "Text: " << Arduino.getAdtext() << endl;


    while (1) {
        showMenu();
    }

    return 0;
}