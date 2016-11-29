#include "include_lib.h"

GerenciadorMem::GerenciadorMem() :
    maxMemory(0), freeMemory(0), maxSwap(0), freeSwap(0), arquivo("MEMStats.txt")
{
    updateData();
}

void GerenciadorMem::updateData()
{
    //Apago o conteúdo do arquivo...
    std::ofstream eraser;
    eraser.open(arquivo, std::ofstream::out | std::ofstream::trunc);
    eraser.close();

    std::stringstream temp;
    temp << "grep \"MemTotal|^MemFree|^SwapTotal|^SwapFree\" -E /proc/meminfo | awk '{print $2}'" <<
    " > " << arquivo;

    system(temp.str().c_str());

    readFromFile();
}

double GerenciadorMem::getMemPercent()
{
    return ((double)freeMemory/maxMemory)*100;
}

double GerenciadorMem::getSwapPercent()
{
    return ((double)freeSwap/maxSwap)*100;
}

bool GerenciadorMem::readFromFile()
{

    std::string temp;
    std::ifstream channel;
    std::vector<long int> readValues;

    channel.open(arquivo);
    if(channel.is_open()){
        while(!channel.eof()){
            while(channel >> temp or !channel.eof()){
                readValues.push_back(std::stol(temp));

                if(readValues.size() == 4)
                {
                    this->maxMemory = readValues.at(0);
                    this->freeMemory = readValues.at(1);
                    this->maxSwap = readValues.at(2);
                    this->freeSwap = readValues.at(3);
                    return true;
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
