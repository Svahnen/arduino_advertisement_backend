#include <iostream>
#include "advertisment.hpp"

using namespace std;

Advertisments ad;
Advertisments adArray[MAX_NUMBER_OF_ADVERTISMENT];

int setAd(int sum, string text)
{

    for (long unsigned int i = 0; i < sizeof(adArray) / sizeof(adArray[0]); i++)
    {
        if (adArray[i].adSum == 0)
        {
            adArray[i].adSum = sum;
            adArray[i].adText = text;

            cout << "Array " << i << " = " << adArray[i].adSum << endl;
            cout << "Array " << i << " = " << adArray[i].adText << endl;
            cout << endl;

            return 0;
        }
    }

    return 0;
}

int deleteAd(int numberOfAd)
{
    adArray[numberOfAd].adSum = 0;
    adArray[numberOfAd].adText = "";

    return 0;
}

string getAdtextByNumber(int x)
{
    return adArray[x].adText;
}

int getNumberOfAdvertisments()
{
    int numberOfAdvertisments = 0;
    for (unsigned long int i = 0; i < sizeof(adArray) / sizeof(adArray[0]); i++)
    {
        if (adArray[i].adSum != 0)
        {
            numberOfAdvertisments++;
        }
    }

    return numberOfAdvertisments;
}

int getadSumByNumber(int x)
{
    return adArray[x].adSum;
}

int getTotalAdSum()
{
    int totalSum = 0;
    for (int i = 0; i < MAX_NUMBER_OF_ADVERTISMENT; i++)
    {
        totalSum += adArray[i].adSum;
    }
    return totalSum;
}