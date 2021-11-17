#include "serial.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Serial Arduino;

int SetSerialConnection(int argc, char **argv) {

    Arduino.numberOfConnections = argc -1;
    Arduino.arduinos = new ofstream[argc -1];
    Arduino.serialPort = new string[argc -1];

    for (int i = 1; i < argc; i++) {
        Arduino.serialPort[i -1] = argv[i];
    }
    return 0;
}

int getNumberOfConnections() {
    return Arduino.numberOfConnections;
}

string getSerialPort(int x) {
    return Arduino.serialPort[x];
}

Serial* getArduino() {
    return &Arduino;
}