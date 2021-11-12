#ifndef ADVERTISMENT_HPP
#define ADVERTISMENT_HPP

#include <iostream>

#define MAX_NUMBER_OF_ADCHARS 32
#define MAX_NUMBER_OF_ADVERTISMENT 10
#define MAX_ADVERTISMENT_COST 10000
#define MIN_ADVERTISMENT_COST 1000

typedef struct {
    int adSum;
    std::string adText;
} Advertisments;

int setAd(int sum, std::string text);
std::string getAdtextByNumber(int x);
int getadSumByNumber(int x);
int getNumberOfAdvertisments();
int deleteAd(int numberOfAd);
int getTotalAdSum();

#endif /* ifndef ADVERTISMENT_HPP */
