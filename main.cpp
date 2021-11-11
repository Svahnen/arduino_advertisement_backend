#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <unistd.h>
#include "advertisment.hpp"

using namespace std;

static int addAd() {
    int sum;
    string adText;

    cout << "Enter sum: ";
    cin >> sum;
    cout << "Enter text: ";
    cin >> adText;

    setAd(sum, adText);

    cout << "You have added an ad" << endl;
    return 0;
}

static int viewAd() {
    int numbersOfArray, i;
    string ad;
    numbersOfArray = getNumberOfAdvertisments();
    cout << endl;
    cout << "Number of arrays: " << numbersOfArray << endl;

    for (i = 0; i < numbersOfArray; i++) {
        ad = getAdtextByNumber(i);
        cout << "Array " << i << ": " << ad << endl;
    }
    cout << endl;
    
    cout << "You have viewed all ads" << endl;
    cout << endl;
    return 0;
}

static int deleteAd() {
    cout << "You have deleted an ad" << endl;
    return 0;
}

int printToFile() {
    string ad;
    ad = getAdtextByNumber(0);
    if (ad == "") {
        cout << endl;
        cout << "There is no ad to be displayed" << endl;
        cout << endl;
        return -1;
    }
    
    int key = 0;
    int numberOfPrints = 0;

    ofstream myfile;
    myfile.open ("example.txt");

    cout << "Press space to exit the loop" << endl;

    while (key != 32) {
        myfile << ad << endl;
        numberOfPrints ++;

        sleep(1);

        if(_kbhit()) {
            key = _getch();
            cout << "Number of prints = " << numberOfPrints << endl;
        }
    }

    myfile.close();
    cout << "You have exit the print loop" << endl;
    return 0;
}

static int showMenu() {
    int choice;
    cout << "1. Add advertisment" << endl;
    cout << "2. View advertisment" << endl;
    cout << "3. Delete advertisment" << endl;
    cout << "4. Print to file" << endl;
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
    case 4:
        printToFile();
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

    while (1) {
        showMenu();
    }

    return 0;
}