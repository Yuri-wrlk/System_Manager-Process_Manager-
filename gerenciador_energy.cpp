#include "include_lib.h"


Gerenciador_Energy::Gerenciador_Energy() : arquivo("EnergyStats.txt")
{
    remainingTimeInMin = 9999;
    updateData();
}

void Gerenciador_Energy::updateData()
{
    //Apago o conteúdo do arquivo...
    std::ofstream eraser;
    eraser.open(arquivo, std::ofstream::out | std::ofstream::trunc);
    eraser.close();

    std::stringstream temp;
    temp << "acpi -b > " << arquivo;

    system(temp.str().c_str());

    readFromFile();
}

int Gerenciador_Energy::getBatteryPercent()
{
    return batteryPercent;
}

double Gerenciador_Energy::getRemainingTimeMin()
{
    return remainingTimeInMin;
}


bool Gerenciador_Energy::readFromFile()
{

    std::string temp;
    std::ifstream channel;
    std::vector<std::string> readValues;
    std::string tempValue;
    int i;
    int hours;
    int min;
    int sec;



    channel.open(arquivo);
    if(channel.is_open()){
        while(!channel.eof()){
            while(channel >> temp or !channel.eof()){
                readValues.push_back(temp);

                if(readValues.size() == 4)
                {
                    if(readValues[3][3] == '%')
                    {
                        batteryPercent = 100;
                        channel.close();
                        return true;
                    }
                    else
                    {
                        batteryPercent = ((readValues[3][0] - 48) * 10) + ((readValues[3][1] - 48));

                    }
                }

                if(readValues.size() == 5)
                {
                    i = 0;
                    while(readValues[4][i] != ':')
                    {
                        tempValue += readValues[4][i];
                        i++;
                    }
                    hours = std::stol(tempValue);
                    tempValue.clear();
                    i++;
                    while(readValues[4][i] != ':')
                    {
                        tempValue += readValues[4][i];
                        i++;
                    }
                    min = std::stol(tempValue);
                    tempValue.clear();
                    i++;
                    while( i < readValues[4].size()  )
                    {
                        tempValue += readValues[4][i];
                        i++;
                    }
                    sec = std::stol(tempValue);
                    tempValue.clear();
                    remainingTimeInMin = ((hours * 3600) + (min * 60) + sec);

                    channel.close();
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
