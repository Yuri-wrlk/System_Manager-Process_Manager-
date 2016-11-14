#include <limits>
#include "gerenciador_cpu.h"



Gerenciador_cpu::Gerenciador_cpu() :  nCpus(0), arquivo("CPUStats.txt")
{
    std::stringstream temp;
    std::string amount;
    std::ifstream cpufile;

    temp << "nproc > " << arquivo;
    system(temp.str().c_str());

    cpufile.open(arquivo, std::ifstream::in);
    if(cpufile >> amount)
        nCpus = std::stol(amount);

    updateParameters();
}

int Gerenciador_cpu::getNCpus()
{
    return nCpus;
}

void Gerenciador_cpu::updateParameters()
{
    //Clearing previous values
    for (int i = 0; i < totalCpu.size(); ++i) {

        totalCpu[i].clear();
    }
    totalCpu.clear();
    cpuUsage.clear();
    maxCpu.clear();

    totalCpu.resize(nCpus + 1);
    cpuUsage.resize(nCpus);
    maxCpu.resize(nCpus);

    std::stringstream temp;

    temp << "grep \"^cpu\" -E /proc/stat | awk '{printf (\"%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\\n\", $2,$3,$4,$5,$6,$7,$8,$9)}'" <<
            " > " << arquivo;

    system(temp.str().c_str());

    readFromFile();

    for(auto i(0); i < nCpus; ++i)
    {
        cpuUsage[i] =    totalCpu.at(i + 1).at(0) + totalCpu.at(i + 1).at(1) + totalCpu.at(i + 1).at(2)
                            + totalCpu.at(i + 1).at(5) + totalCpu.at(i + 1).at(6) + totalCpu.at(i + 1).at(7);
        maxCpu[i] =  cpuUsage.at(i) + (totalCpu.at(i + 1).at(3) + totalCpu.at(i + 1).at(4));
    }

}

QVector<double> Gerenciador_cpu::calculateUsage()
{
    QVector<double> cpuPercentage;
    for(int i = 0; i < nCpus; ++i)
    {
        cpuPercentage.push_back((cpuUsage[i] / static_cast<double>(maxCpu[i])) * 100);
    }
    return cpuPercentage;
}

bool Gerenciador_cpu::readFromFile()
{

    std::string temp;
    std::ifstream channel;
    long int temp_value;
    int pos(0);

    channel.open(arquivo);
    if(channel.is_open()){
        while(!channel.eof()){
            while(channel >> temp or !channel.eof()){
                temp_value = std::stol(temp);
                totalCpu[pos].push_back(temp_value);
                if(totalCpu[pos].size() == 8)
                {
                    pos++;
                    if(pos == nCpus + 1)
                        return true;
                }
            }
            if(temp == "\0") std::getline(channel,temp);
        }
        return true;
    }
    else{
        std::cout << "Houston, we've a problem!" << std::endl;
        return false;
    }
}
