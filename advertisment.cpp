#include <iostream>
#include "advertisment.hpp"

using namespace std;

int Advertisments::setAd(int sum, string text)
{
    this->adSum = sum;
    this->adText = text;

    return 0;
}
string Advertisments::getAdtext() {
    return this->adText;
}

int Advertisments::getadSum() {
    return this->adSum;
}