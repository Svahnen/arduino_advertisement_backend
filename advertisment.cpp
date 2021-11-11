#include <iostream>
#include "advertisment.hpp"

using namespace std;

Advertisments ad;
Advertisments adArray[10];

int setAd(int sum, string text) {
    //ad.adSum = sum;
    //ad.adText = text;

    int len = sizeof(adArray)/sizeof(adArray[0]);

    cout << endl;
    cout << "Array is " << len << " numbers" << endl;
    cout << "Array length is " << len << endl;
    cout << endl;

    for (int i = 0; i < sizeof(adArray)/sizeof(adArray[0]); i++) {
        if (adArray[i].adSum == 0) {
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

string getAdtextByNumber(int x) {
    return adArray[x].adText;
}

int getNumberOfAdvertisments() {
    int numberOfAdvertisments = 0;
    for (int i = 0; i < sizeof(adArray)/sizeof(adArray[0]) ; i++) {
        if (adArray[i].adSum != 0) {
            numberOfAdvertisments ++;
        }
    }
    
    return numberOfAdvertisments;
}

int getadSum() {
    return ad.adSum;
}