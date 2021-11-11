#ifndef ADVERTISMENT_HPP
#define ADVERTISMENT_HPP

#include <iostream>

#define MAX_NUMBER_OF_ADCHARS 32
#define MAX_NUMBER_OF_ADVERTISMENT 10
#define MAX_ADVERTISMENT_COST 10000
#define MIN_ADVERTISMENT_COST 1000

class Advertisments {
private:
    int adSum;
    std::string adText;

public:
    int setAd(int sum, std::string text);
    std::string getAdtext();
    int getadSum();
};

#endif /* ifndef ADVERTISMENT_HPP */
