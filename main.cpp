#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "advertisment.hpp"
#include "serial.hpp"
#include <signal.h>
#include <limits>

using namespace std;

int printing = 0;

// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum)
{
    //TODO: fix bug where ctrl-c is interrupted even in the main menu
    if (signum == 2)
    {
        if (printing)
        {
            cout << endl
                 << "Going to main menu" << endl;
            printing = 0;
        }
        else
        {
            exit(EXIT_SUCCESS);
        }
    }
}

static int addAd()
{
    int sum, numbersOfArray;
    string adText;
    numbersOfArray = getNumberOfAdvertisments();

    if (numbersOfArray >= MAX_NUMBER_OF_ADVERTISMENT)
    {
        cout << "Max number of advertisments have been added!" << endl;
        return -1;
    }

    cout << "You have " << MAX_NUMBER_OF_ADVERTISMENT - numbersOfArray << " free slots of advertisment to add" << endl;
    cout << "Enter sum between " << MIN_ADVERTISMENT_COST << " - " << MAX_ADVERTISMENT_COST << " and a message with a maximum of " << MAX_NUMBER_OF_ADCHARS << " characters" << endl;
    cout << "Enter sum: ";

    while (!(cin >> sum))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "The sum needs to be a number" << endl;
        cout << "Enter sum: ";
    }

    if (sum > MAX_ADVERTISMENT_COST || sum < MIN_ADVERTISMENT_COST)
    {
        cout << "You need to enter a number between " << MIN_ADVERTISMENT_COST << " and " << MAX_ADVERTISMENT_COST << endl;
        return -1;
    }

    cout << "Enter text: ";
    cin.ignore();
    getline(cin, adText, '\n');

    if (adText.length() > MAX_NUMBER_OF_ADCHARS || adText.length() < 1)
    {
        cout << "Error: enter a message between 1 and " << MAX_NUMBER_OF_ADCHARS << " characters" << endl;
        return -1;
    }

    setAd(sum, adText);

    cout << "You have added an ad" << endl;
    return 0;
}

static int viewAd()
{
    int numbersOfArray, i;
    string ad;
    numbersOfArray = getNumberOfAdvertisments();
    cout << endl;
    cout << "Number of ads in array: " << numbersOfArray << endl;

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
    cout << "Enter which ad you want to remove by entering the array index number: ";
    cin >> input;
    // Check that the input is correct

    // TODO: Add error handeling in case user tries to delete and array that does not exist
    deleteAd(input);
    cout << "You have deleted an ad" << endl;
    cout << endl;
    return 0;
}

void writeToSerial(string ad, int i)
{
    Serial *Arduino;
    Arduino = getArduino();

    Arduino->arduinos[i] << ad;
    Arduino->arduinos[i].flush();
}

void openSerial(string serial, int i)
{
    Serial *Arduino;        //The * makes this only a pointer not an actual struct
    Arduino = getArduino(); // connect the struct pointer to the struct inside serial.cpp

    Arduino->arduinos[i].open(serial);
}

void closeSerial(int i)
{
    Serial *Arduino;
    Arduino = getArduino();

    Arduino->arduinos[i].close();
}

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
        totalSec[j] = ((adSum[j] / totalSum) * 60); //Seconds to display all messages
        cout << "Total seconds to display ad " << j << " is: " << totalSec[j] << endl;
    }

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
    cout << "Now printing messages" << endl;
    cout << "Press ctrl-c to pause the print loop and go back to the menu" << endl;

    printing = 1;
    // This loop should be interupted by ctrl-c
    while (printing)
    {
        for (int x = 0; x < numbersOfAds; x++)
        {
            for (int i = 0; i < numbersOfConnections; i++)
            {
                if (printing)
                {
                    writeToSerial(ads[x], i);
                }
            }
            //Here will be foor loop that does writeToSerial for all argv: DONE ABOVE!
            if (printing) // dont sleep if ctrl-c have been pressed
            {
                sleep(totalSec[x]); // The current sleep command is interrupted bu ctrl-c
            }
        }
    }

    cout << "Pausing print loop" << endl;
    //Here we going to close all the open connections.
    for (int i = 0; i < numbersOfConnections; i++)
    {
        cout << "You have closed connection " << i + 1 << endl;
        closeSerial(i);
    }
    printing = 0;
    return 0;
}

static int showMenu()
{
    char choice;
    cout << "1. Add advertisment" << endl;
    cout << "2. View advertisements" << endl;
    cout << "3. Delete advertisment" << endl;
    cout << "4. Print to Arduino/s" << endl;
    cout << "0. Quit program" << endl;
    cout << "Enter menu choice: ";
    cin >> choice;

    // See if the user entered a number
    try
    {
        stoi(&choice);
    }
    catch (const exception &e)
    {
        cerr << "You need to enter a number" << endl;
        return -1;
    }

    switch (stoi(&choice))
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
        printToSerial();
        break;
    case 0:
        cout << "You have exited the program" << endl;
        exit(EXIT_SUCCESS);
    default:
        cout << "Please choose a correct menu alternative!" << endl;
        break;
    }
    return 0;
}

int main(int argc, char **argv) //argc the amount of arguments + filename, argv the arguments
{
    // Register signal and signal handler
    signal(SIGINT, signal_callback_handler);

    if (argc == 1)
    {
        cout << "Too few arguments, run program with: " << argv[0] << " serialports seperated with space" << endl;
        return -1;
    }

    cout << "Have " << argc - 1 << " argument/s:" << endl;
    for (int i = 1; i < argc; ++i)
    {
        cout << argv[i] << endl;
    }

    SetSerialConnection(argc, argv);

    while (1)
    {
        showMenu();
    }
    deleteStruct();
    return 0;
}