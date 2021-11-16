#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "advertisment.hpp"

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

    ofstream myfile;
    myfile.open("/dev/cu.usbmodem11301"); //Serial port
    sleep(3);

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
        cout << "You have quitted the program" << endl;
        exit(EXIT_SUCCESS);
    default:
        cout << "Please enter a correct choice!" << endl;
        break;
    }
    return 0;
}

int main(int argc, char **argv)
{
    cout << "Have " << argc - 1 << " arguments:" << endl;
    for (int i = 1; i < argc; ++i)
    {
        cout << argv[i] << endl;
    }

    while (1)
    {
        showMenu();
    }

    return 0;
}