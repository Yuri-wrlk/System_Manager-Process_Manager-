
#include "include_lib.h"


class Gerenciador{
	private:
		std::vector<Processo> listaProcessos;
		std::string arquivo;
		std::string json;
        int familyCount;

		void swap(int a, int b){
            Processo temp = listaProcessos[a];
            listaProcessos[a] = listaProcessos[b];
            listaProcessos[b] = temp;
		}

	public:

        Gerenciador(std::string n_arquivo = "VeryImportantFile.txt",
                    std::string n_json = "processList.json"): arquivo(n_arquivo), json(n_json){
			std::ofstream eraser; // Eu preciso do json limpo.
			eraser.open(json, std::ofstream::out | std::ofstream::trunc);
			eraser.close();

            this->load(this->arquivo);
		}
		inline std::vector<Processo> getListaProcessos(){ return this->listaProcessos; }
		inline std::string getNomeArquivo(){ return this->arquivo; }
		inline std::string getJSON(){ return this->json; }


        void load(std::string arquivo){
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
		}

		void makeFamily(std::vector<Processo> & lista, int begin){
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

        void printFilePath (){
            char jsfull_path[PATH_MAX];
            char flfull_path[PATH_MAX];

            realpath(json.c_str(), jsfull_path);
            realpath(arquivo.c_str(), flfull_path);

            std::cout << "O caminho para o arquivo json é: " << jsfull_path << std::endl;
            std::cout << "O caminho para o arquivo de dados é: " << flfull_path << std::endl;

        }

        void update (){
            familyCount = 0;
            load(arquivo);
            makeFamily(listaProcessos, 0);
        }


        void toJSON(std::vector<Processo> & lista, int begin, int limit,
                    bool firstTime = false, bool lastTime = false)
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
                    writer << "\t\t\t\t{" << lista[count].toString() << "}";
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
                    writer << "\t\t\t\t{" << lista[count].toString() << "}";
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
                    writer << "\t\t\t\t{" << lista[count].toString() << "}";
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
};
