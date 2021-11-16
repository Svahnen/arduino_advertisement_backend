#ifndef SERIAL_HPP
#define SERIAL_HPP
#include <fstream>

typedef struct
{
    int numberOfConnections;
    std::string *serialPort;
    std::ofstream *arduinos;
} Serial;

int SetSerialConnection(int argc, char **argv);
int getNumberOfConnections();
std::string getSerialPort(int x);
Serial* getArduino();

#endif /* ifndef SERIAL_HPP */


