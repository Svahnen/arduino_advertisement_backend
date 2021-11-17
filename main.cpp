#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "advertisment.hpp"
#include "serial.hpp"

using namespace std;

static int addAd()
{
    int sum, numbersOfArray;
    string adText;
    numbersOfArray = getNumberOfAdvertisments();

    if (numbersOfArray > MAX_NUMBER_OF_ADVERTISMENT)
    {
        cout << "Max number of advertisments have been added!" << endl;
        return -1;
    }

    cout << "You have " << MAX_NUMBER_OF_ADVERTISMENT - numbersOfArray << " free slots of advertisment to add" << endl;
    cout << "Enter sum between " << MIN_ADVERTISMENT_COST << " - " << MAX_ADVERTISMENT_COST << " and max number of characters is " << MAX_NUMBER_OF_ADCHARS << endl;
    cout << "Enter sum: ";
    cin >> sum;
    cout << "Enter text: ";
    cin.ignore();
    getline(cin, adText, '\n');

    if (sum > MAX_ADVERTISMENT_COST || sum < MIN_ADVERTISMENT_COST || adText.length() > MAX_NUMBER_OF_ADCHARS || adText.length() < 0)
    {
        cout << "Please enter correct input!" << endl;
        return -1;
    }

    setAd(sum, adText);

    cout << "You have added an ad" << endl;
    return 0;
}

static int viewAd()
{
    int numbersOfArray, i, j;
    string ad;
    numbersOfArray = getNumberOfAdvertisments();
    cout << endl;
    cout << "Number of arrays: " << numbersOfArray << endl;

    for (i = 0; i < MAX_NUMBER_OF_ADVERTISMENT; i++)
    {
        ad = getAdtextByNumber(i);
        if (ad != "")
        {
            cout << "Array " << i << ": " << ad << endl;
        }
    }
    cout << endl;
    return 0;
}

static int removeAd()
{
    int input;
    viewAd();
    cout << "Enter which ad you want to remove by enter array number: ";
    cin >> input;
    // Check that the input is correct

    deleteAd(input);
    cout << "You have deleted an ad" << endl;
    cout << endl;
    return 0;
}

static int printToFile()
{
    string ads[10];
    string ad;
    int numbersOfAds, i, totalSum;
    double adSum[10], totalSec[10];
    numbersOfAds = 0;

    for (i = 0; i < MAX_NUMBER_OF_ADVERTISMENT; i++)
    {
        ad = getAdtextByNumber(i);
        if (ad != "")
        {
            ads[numbersOfAds] = ad;
            adSum[numbersOfAds] = getadSumByNumber(numbersOfAds);
            numbersOfAds++;
        }
    }

    if (numbersOfAds <= 0)
    {
        cout << endl;
        cout << "There is no ad to be displayed" << endl;
        cout << endl;
        return -1;
    }

    totalSum = getTotalAdSum();

    for (int j = 0; j < numbersOfAds; j++)
    {
        totalSec[j] = ((adSum[j] / totalSum) * 10); //Seconds to display all messages
        cout << "Total sec for ad " << j << " is: " << totalSec[j] << endl;
    }

    int key = 0;

    ofstream myfile;
    myfile.open("example.txt");
    sleep(3);

    cout << "Press enter to exit the loop" << endl;

    while (1)
    {
        for (int x = 0; x < numbersOfAds; x++)
        {
            myfile << ads[x] << endl;
            myfile.close();
            sleep(totalSec[x]);
        }
    }
    return 0;
}

void writeToSerial(string ad, int i)
{
    Serial *Arduino;
    Arduino = getArduino();

    Arduino->arduinos[i] << ad;
    Arduino->arduinos->flush();

    //ofstream arduino;
    //arduino << ad;
    //arduino.flush();
}

void openSerial(string serial, int i)
{
    Serial *Arduino;        //The * makes this only a pointer not an actual struct
    Arduino = getArduino(); // connect the struct pointer to the struct inside serial.cpp

    Arduino->arduinos[i].open(serial);

    //ofstream arduino;
    //arduino.open(serial);
    //sleep(3);
}

void closeSerial(int i)
{
    Serial *Arduino;
    Arduino = getArduino();

    Arduino->arduinos[i].close();

    //arduino.close();
}

/* 
int writeToSerial(string serial, string ad, double sec)
{
    ofstream arduino;

    arduino.open(serial);
    if (!arduino.is_open())
    {
        sleep(2);
    }

    arduino << ad;
    arduino.flush();
    sleep(sec);
    //arduino.close();

    return 0;
} */

static int printToSerial()
{
    string ads[10];
    string ad;
    int numbersOfAds, i, totalSum;
    double adSum[10], totalSec[10];
    numbersOfAds = 0;

    for (i = 0; i < MAX_NUMBER_OF_ADVERTISMENT; i++)
    {
        ad = getAdtextByNumber(i);
        if (ad != "")
        {
            ads[numbersOfAds] = ad;
            adSum[numbersOfAds] = getadSumByNumber(numbersOfAds);
            numbersOfAds++;
        }
    }

    if (numbersOfAds <= 0)
    {
        cout << endl;
        cout << "There is no ad to be displayed" << endl;
        cout << endl;
        return -1;
    }

    totalSum = getTotalAdSum();

    for (int j = 0; j < numbersOfAds; j++)
    {
        totalSec[j] = ((adSum[j] / totalSum) * 10); //Seconds to display all messages
        cout << "Total sec for ad " << j << " is: " << totalSec[j] << endl;
    }

    int key = 0;

    /*
    ofstream myfile;
    int count = 0;

    while (count < 1)
    {
        myfile.open("/dev/cu.usbmodem11401"); //Serial port
        sleep(3);
        for (int x = 0; x < numbersOfAds; x++)
        {
            myfile << ads[x];
            myfile.flush();
            sleep(totalSec[x]);
        }
        count++;
        myfile.close();
    }
    */

    int numbersOfConnections = getNumberOfConnections();
    cout << "Number of connections: " << numbersOfConnections << endl;
    string serialPort;

    for (int i = 0; i < numbersOfConnections; i++)
    {
        serialPort = getSerialPort(i);
        cout << "Serialport: " << serialPort << endl;
        openSerial(serialPort, i);
    }
    sleep(3); // sleep so the arduinos have a chance to setup the serial port

    int count = 0;
    int wts = 0;
    while (count < 2)
    {
        //Maybe we have to change these for loops!
        for (int x = 0; x < numbersOfAds; x++)
        {
            for (int i = 0; i < numbersOfConnections; i++)
            {
                writeToSerial(ads[x], i);
                wts++;
            }
            cout << "Number of times you write to Serial: " << wts << endl;
            //Here will be foor loop that does writeToSerial for all argv: DONE ABOVE!
            //writeToSerial("/dev/cu.usbmodem11401", ads[x]);
            sleep(totalSec[x]); // sleep should come after for loop with writeToSerial
        }

        count++; // temporary test to stop the loop after x amount
    }

    //Here we going to close all the open files/serial connections.
    for (int i = 0; i < numbersOfConnections; i++)
    {
        cout << "You have closed " << i + 1 << " connections" << endl;
        closeSerial(i);
    }

    return 0;
}

static int showMenu()
{
    int choice;
    cout << "1. Add advertisment" << endl;
    cout << "2. View advertisment" << endl;
    cout << "3. Delete advertisment" << endl;
    cout << "4. Print to file" << endl;
    cout << "5. Print to Arduino" << endl;
    cout << "0. Quit program" << endl;
    cout << "Enter menu choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        addAd();
        break;
    case 2:
        viewAd();
        break;
    case 3:
        removeAd();
        break;
    case 4:
        printToFile();
        break;
    case 5:
        printToSerial();
        break;
    case 0:
        //closeSerial("/dev/cu.usbmodem11401");
        cout << "You have quitted the program" << endl;
        exit(EXIT_SUCCESS);
    default:
        cout << "Please enter arduino correct choice!" << endl;
        break;
    }
    return 0;
}

int main(int argc, char **argv) //argc the amount of arguments + filename
{
    /*
    Serial Arduino;
    Arduino = getArduino();

    ofstream Arduino.arduinos;
    Arduino.arduinos = new ofstream[5];


    arduino[0].open("/dev/cu.usbmodem11401");
    sleep(3);
    arduino[0] << "test";
    arduino[0].flush();
    arduino[0].close();
    */

    cout << "Have " << argc - 1 << " arguments:" << endl;
    for (int i = 1; i < argc; ++i)
    {
        cout << argv[i] << endl;
    }

    SetSerialConnection(argc, argv);

    while (1)
    {
        showMenu();
    }

    return 0;
}