#ifndef PROCESSO_H
#define PROCESSO_H

#include "include_lib.h"

class Processo {


private:

    std::string nome;
    int pid;
    int ppid;
    int threads;
    enum Print_parameter size; // define o tamanho do circulo.
    double cpu;
    double mem;



public:

    Processo(std::string nome, int pid, int ppid, int threads) :
    nome(nome) ,pid(pid), ppid(ppid), threads(threads), size(Print_parameter::THREADS){}

    Processo(std::string nome, std::string pid, std::string ppid, std::string threads) :
    nome(nome), pid(stoi(pid)), ppid(stoi(ppid)), threads(stoi(threads)){}

    inline std::string getNome(){ return this->nome; }
    inline int getPid(){ return this->pid; }
    inline int getPPid(){ return this->ppid; }
    inline int getThreads(){ return this->threads; }
    inline double getCpu () { return this->cpu; }
    inline double getMem () { return this->mem; }
    inline std::string toString(Print_parameter type){
        std::stringstream temp;

        switch(type){
            case Print_parameter::CPU :
                if(cpu == 0.0){
                    temp << "\"name\": \"" << this->nome << "\", " << "\"size\": " << (static_cast<int>(this->cpu + 1)*2) << ", "
                    << "\"pid\": " << this->pid;
                }
                else{
                    temp << "\"name\": \"" << this->nome << "\", " << "\"size\": " << (static_cast<int>(this->cpu + 1)*10) << ", "
                    << "\"pid\": " << this->pid;
                }
                break;
            case Print_parameter::MEM :
                if(mem == 0.0){
                    temp << "\"name\": \"" << this->nome << "\", " << "\"size\": " << (static_cast<int>(this->mem + 1)*2) << ", "
                    << "\"pid\": " << this->pid;
                }
                else{
                    temp << "\"name\": \"" << this->nome << "\", " << "\"size\": " << (static_cast<int>(this->mem + 1)*10) << ", "
                    << "\"pid\": " << this->pid;
                }
                break;
            default :
                temp << "\"name\": \"" << this->nome << "\", " << "\"size\": " << this->threads*10 << ", "
                << "\"pid\": " << this->pid;
                break;

        }
        return temp.str();
    }

    inline void setNome(std::string nome){ this->nome = nome;}
    inline void setPid(int pid){ this->pid = pid ;}
    inline void setPPid(int ppid){this->ppid = ppid;}
    inline void setThreads(int threads){ this->threads = threads;}
    inline void setCpu(double cpu){ this->cpu = cpu;}
    inline void setMem(double mem){ this->mem = mem;}
    inline void setSize(Print_parameter printp) {this->size = printp;}

    void setAll(std::string nome, int pid, int ppid, int threads){
        this->setNome(nome);
        this->setPid(pid);
        this->setPPid(ppid);
        this->setThreads(threads);
    }

    bool compare(Processo proc){
        return (this->ppid == proc.getPPid());
    }

};

#endif // PROCESSO_H
