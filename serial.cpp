#include "serial.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Serial *Arduino;

Serial::Serial(int nPorts)
{
    numberOfConnections = nPorts;
    arduinos = new ofstream[nPorts];
    serialPort = new string[nPorts];
}

Serial::~Serial()
{
    delete[] arduinos;
    delete[] serialPort;
}

int SetSerialConnection(int argc, char **argv)
{

    Arduino = new Serial(argc - 1);
    // creates a string array that's as long as the nr of arguments

    for (int i = 1; i < argc; i++)
    {
        Arduino->serialPort[i - 1] = argv[i]; // Save argument string in this array index
    }
    return 0;
}

int getNumberOfConnections()
{
    return Arduino->numberOfConnections;
}

string getSerialPort(int x)
{
    return Arduino->serialPort[x];
}

Serial *getArduino() // Returns a pointer to the Arduino struct
{
    return Arduino;
}

void deleteStruct()
{
    delete Arduino;
}