#include "include_lib.h"
#include "Gerenciador.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Gerenciador * ger = new Gerenciador();
    ger->update();
    Gerenciador_cpu * gercpu = new Gerenciador_cpu();
    QVector<double> cpuPercent (gercpu->calculateUsage());
    for(int i = 0; i < gercpu->getNCpus(); ++i)
    {
        std::cout << "O uso da cpu de número " << i << " é " << cpuPercent[i] << std::endl;
    }
    return a.exec();
}
