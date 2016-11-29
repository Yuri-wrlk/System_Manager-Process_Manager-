#ifndef GERENCIADOR_ENERGY_H
#define GERENCIADOR_ENERGY_H

#include "include_lib.h"

class Gerenciador_Energy
{
private:
    std::string arquivo;
    int batteryPercent;
    double remainingTimeInMin;
    bool readFromFile();

public:
    Gerenciador_Energy();
    void updateData();
    int getBatteryPercent();
    double getRemainingTimeMin();

};


#endif // GERENCIADOR_ENERGY_H
