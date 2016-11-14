#ifndef PROCESSO_H
#define PROCESSO_H

#include<string>
#include<fstream>

class Processo {
private:

    std::string nome;
    int pid;
    int ppid;
    int threads;
    int size; // define o tamanho do circulo.

public:

    Processo(std::string nome, int pid, int ppid, int threads) :
    nome(nome) ,pid(pid), ppid(ppid), threads(threads){}

    Processo(std::string nome, std::string pid, std::string ppid, std::string threads) :
    nome(nome), pid(stoi(pid)), ppid(stoi(ppid)), threads(stoi(threads)){}

    inline std::string getNome(){ return this->nome; }
    inline int getPid(){ return this->pid; }
    inline int getPPid(){ return this->ppid; }
    inline int getThreads(){ return this->threads; }
    inline std::string toString(){
        std::stringstream temp;
        temp << "\"name\": \"" << this->nome << "\", " << "\"size\": " << this->threads*200 << ", "
        << "\"pid\": " << this->pid;

        return temp.str();
    }

    inline void setNome(std::string nome){ this->nome = nome;}
    inline void setPid(int pid){ this->pid = pid ;}
    inline void setPPid(int ppid){this->ppid = ppid;}
    inline void setThreads(int threads){ this->threads = threads;}

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
