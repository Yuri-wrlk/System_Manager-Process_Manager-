#ifndef GERENCIADOR
#define GERENCIADOR

#include "include_lib.h"


class Gerenciador{
	private:
		std::vector<Processo> listaProcessos;
		std::string arquivo;
		std::string json;
        int familyCount;
        Print_parameter printType;

        void swap(int a, int b);

	public:

        Gerenciador(std::string n_arquivo = "VeryImportantFile.txt",
                    std::string n_json = "processList.json");
		inline std::vector<Processo> getListaProcessos(){ return this->listaProcessos; }
		inline std::string getNomeArquivo(){ return this->arquivo; }
		inline std::string getJSON(){ return this->json; }
        inline void setPrintType(Print_parameter printType) { this->printType = printType; }

        void load(std::string arquivo);
        void insertCpuMem ( );
        void makeFamily(std::vector<Processo> & lista, int begin);
        void printFilePath ();
        void update ();
        void toJSON(std::vector<Processo> & lista, int begin, int limit,
                    bool firstTime = false, bool lastTime = false);
};

#endif
