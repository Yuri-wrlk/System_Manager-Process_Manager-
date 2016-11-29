#ifndef GERENCIADOR_MEM_H
#define GERENCIADOR_MEM_H

#include "include_lib.h"

class GerenciadorMem
{
private:
    long int maxMemory;
    long int freeMemory;
    long int maxSwap;
    long int freeSwap;
    std::string arquivo;
    bool readFromFile();

public:
    GerenciadorMem();
    void updateData();
    double getMemPercent();
    double getSwapPercent();

};

#endif // GERENCIADOR_MEM_H
