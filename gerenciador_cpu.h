#ifndef GERENCIADOR_CPU_H
#define GERENCIADOR_CPU_H

#include "include_lib.h"

class Gerenciador_cpu
{
private:
    int nCpus;
    std::string arquivo;
    QVector<QVector<long int>>  totalCpu;
    QVector<long int> maxCpu;
    QVector<long int> cpuUsage;

    bool readFromFile();

public:

    Gerenciador_cpu();
    int getNCpus();
    void updateParameters();
    QVector<double> calculateUsage();
};

#endif // GERENCIADOR_CPU_H
