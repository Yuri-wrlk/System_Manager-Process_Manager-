#include "include_lib.h"

Gerenciador::Gerenciador(std::string n_arquivo,
            std::string n_json): arquivo(n_arquivo), json(n_json){
    std::ofstream eraser; // Eu preciso do json limpo.
    eraser.open(json, std::ofstream::out | std::ofstream::trunc);
    eraser.close();
    printType = Print_parameter::THREADS;
    this->load(this->arquivo);
}

void Gerenciador::swap(int a, int b){
    Processo temp = listaProcessos[a];
    listaProcessos[a] = listaProcessos[b];
    listaProcessos[b] = temp;
}

void Gerenciador::load(std::string arquivo){
    //Apago o conteúdo do arquivo...
    std::ofstream eraser;
    eraser.open(arquivo, std::ofstream::out | std::ofstream::trunc);
    eraser.close();

    //Escrevo nele novamente.
    std::stringstream temp;
    temp << "grep \"Name|^Pid|^PPid|^Threads\" -E /proc/[0-9]*/status | awk '{print $2}'" <<
    " > " << arquivo;

    system(temp.str().c_str());

    this->listaProcessos.clear();
    read(this->arquivo, this->listaProcessos);
    insertCpuMem();
}

void Gerenciador::insertCpuMem ( ){
    //Apago o conteúdo do arquivo...
    std::ofstream eraser;
    eraser.open(arquivo, std::ofstream::out | std::ofstream::trunc);
    eraser.close();

    //Escrevo nele novamente.
    std::stringstream temp;
    temp << "ps -e -o pid,pcpu,pmem" <<
    " > " << arquivo;

    system(temp.str().c_str());

    std::vector<std::string> Content;
    std::string auxiliary;
    std::ifstream channel;

    int pid_proc;

    channel.open(arquivo);

    std::getline(channel,auxiliary); // We want to ignore the first line entirely
    if(channel.is_open()){
        while(!channel.eof()){
            while(channel >> auxiliary or !channel.eof()){
                Content.push_back(auxiliary);

                if(Content.size() == 3){
                    pid_proc = stoi(Content.at(0));
                    for(Processo proc : listaProcessos){
                        if(proc.getPid() == pid_proc){
                            proc.setCpu(stod(Content.at(1)));
                            proc.setMem(stod(Content.at(2)));
                            break;
                        }
                    }
                    Content.clear();
                }
            }
            if(auxiliary == "\0") std::getline(channel,auxiliary);
        }
    }

}

void Gerenciador::makeFamily(std::vector<Processo> & lista, int begin){
    unsigned int preBegin = begin;
    for(unsigned int counter(begin); counter < lista.size(); counter++)
        for(unsigned int comp(begin); comp < preBegin+1; comp++){
            if(comp != counter && lista[comp].compare(lista[counter])){
                this->swap(counter, ++preBegin);
               // counter = preBegin+1;
                break;
            }
        }

    if(preBegin < lista.size()-1){
        if(begin == 0) this->toJSON(lista, begin, preBegin, true);
        else this->toJSON(lista, begin, preBegin);

        if(preBegin+1 != lista.size()) this->makeFamily(lista, preBegin+1);
    }
    else{
        this->toJSON(lista, begin, preBegin, false, true);
    }
 }

void Gerenciador::printFilePath (){

    char jsfull_path[PATH_MAX];
    char flfull_path[PATH_MAX];

    realpath(json.c_str(), jsfull_path);
    realpath(arquivo.c_str(), flfull_path);

    std::cout << "O caminho para o arquivo json é: " << jsfull_path << std::endl;
    std::cout << "O caminho para o arquivo de dados é: " << flfull_path << std::endl;

}

void Gerenciador::update (){
    familyCount = 0;
    load(arquivo);
    makeFamily(listaProcessos, 0);
}


void Gerenciador::toJSON(std::vector<Processo> & lista, int begin, int limit,
            bool firstTime, bool lastTime)
{

    std::ofstream writer;

    if(firstTime)
    {
        familyCount++;
        //Abrindo o arquivo e executando a limpeza do conteudo anterior
        writer.open(json, std::ofstream::out | std::ofstream::trunc);
        // Deveria ser '{'
        writer << "{\n";
        // Deve ser '   "name": "processos",
        writer << "\t\"name\": \"processos\",\n";
        writer << "\t\"children\":\n";
        writer << "\t[\n";
        writer << "\t\t{\n";
        writer << "\t\t\t\"name\": \"family_number"<< familyCount << "\" ,\n";
        writer << "\t\t\t\"children\":\n";
        writer << "\t\t\t[\n";
        for(auto count(begin); count <= limit; count++)
        {
            writer << "\t\t\t\t{" << lista[count].toString(printType) << "}";
            if(count != limit)
                writer << ",";
            writer << "\n";
        }
        writer << "\t\t\t]\n";
        writer << "\t\t},\n";
        writer.close();
    }
    else if (!lastTime){
        familyCount++;
        writer.open(json, std::ofstream::out | std::ofstream::app);
        writer << "\t\t{\n";
        writer << "\t\t\t\"name\": \"family_number"<< familyCount << "\" ,\n";
        writer << "\t\t\t\"children\":\n";
        writer << "\t\t\t[\n";
        for(auto count(begin); count <= limit; count++)
        {
            writer << "\t\t\t\t{" << lista[count].toString(printType) << "}";
            if(count != limit)
                writer << ",";
            writer << "\n";
        }
        writer << "\t\t\t]\n";
        writer << "\t\t},\n";
        writer.close();
    }
    else{

        familyCount++;
        writer.open(json, std::ofstream::out | std::ofstream::app);
        writer << "\t\t{\n";
        writer << "\t\t\t\"name\": \"family_number"<< familyCount << "\" ,\n";
        writer << "\t\t\t\"children\":\n";
        writer << "\t\t\t[\n";
        for(auto count(begin); count <= limit; count++)
        {
            writer << "\t\t\t\t{" << lista[count].toString(printType) << "}";
            if(count != limit)
                writer << ",";
            writer << "\n";
        }
        writer << "\t\t\t]\n";
        writer << "\t\t}\n";
        writer << "\t]\n";
        writer << "}";
        writer.close();
    }
}
