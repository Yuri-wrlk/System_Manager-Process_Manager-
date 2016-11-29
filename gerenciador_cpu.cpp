#include <limits>
#include "include_lib.h"



Gerenciador_cpu::Gerenciador_cpu() :  nCpus(0), arquivo("CPUStats.txt")
{
    std::stringstream temp;
    std::string amount;
    std::ifstream cpufile;

    //Apago o conteúdo do arquivo...
    std::ofstream eraser;
    eraser.open(arquivo, std::ofstream::out | std::ofstream::trunc);
    eraser.close();


    temp << "nproc > " << arquivo;
    system(temp.str().c_str());

    cpufile.open(arquivo, std::ifstream::in);
    if(cpufile >> amount)
        nCpus = std::stol(amount);


    maxCpu.fill(0, 4);
    cpuUsage.fill(0, 4);

    updateParameters();

}

int Gerenciador_cpu::getNCpus()
{
    return nCpus;
}

void Gerenciador_cpu::updateParameters()
{

    prevMaxCpu = maxCpu;
    prevCpuUsage = cpuUsage;

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

    //Apago o conteúdo do arquivo...
    std::ofstream eraser;
    eraser.open(arquivo, std::ofstream::out | std::ofstream::trunc);
    eraser.close();

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
        cpuPercentage.push_back(((cpuUsage.at(i) - prevCpuUsage.at(i)) * 100)/ static_cast<double>(maxCpu.at(i) - prevMaxCpu.at(i)) );
    }
    return cpuPercentage;
}

bool Gerenciador_cpu::readFromFile()
{

    std::string temp;
    std::ifstream channel;
    int pos(0);

    channel.open(arquivo);
    if(channel.is_open()){
        while(!channel.eof()){
            while(channel >> temp or !channel.eof()){
                totalCpu[pos].push_back(stol(temp));
                if(totalCpu[pos].size() == 8)
                {
                    pos++;
                    if(pos == nCpus + 1){
                        channel.close();
                        return true;
                    }
                }
            }
            if(temp == "\0") std::getline(channel,temp);
        }
        channel.close();
        return true;
    }
    else{
        std::cout << "Houston, we've a problem!" << std::endl;
        return false;
    }
}
