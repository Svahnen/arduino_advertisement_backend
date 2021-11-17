#ifndef SERIAL_HPP
#define SERIAL_HPP
#include <fstream>

struct Serial
{
    int numberOfConnections;
    std::string *serialPort;
    std::ofstream *arduinos;
    Serial(int nPorts);
    ~Serial(); //Will run delete when this struct is out of scope
};

int SetSerialConnection(int argc, char **argv);
int getNumberOfConnections();
std::string getSerialPort(int x);
Serial *getArduino();
void deleteStruct();

#endif /* ifndef SERIAL_HPP */
