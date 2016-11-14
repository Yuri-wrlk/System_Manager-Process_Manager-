#include "include_lib.h"

bool read(std::string File, std::vector<Processo>& processList ){


    processList.clear();
    std::vector<std::string> Content;
    std::string temp;
    std::ifstream channel;
    Processo * temp_proc;

    channel.open(File);
    if(channel.is_open()){
        while(!channel.eof()){
            while(channel >> temp or !channel.eof()){
                Content.push_back(temp);

                if(Content.size() == 4){
                    temp_proc = new Processo (Content.at(0), Content.at(1), Content.at(2), Content.at(3));
                    processList.push_back(*temp_proc);

                    Content.clear();
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
