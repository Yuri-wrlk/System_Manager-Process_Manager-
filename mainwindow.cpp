#include "include_lib.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Setting up the UI
    ui->setupUi(this);

    //Setting a list of useable colors
    setColors();

    //Instantiating the managers;
    procGerenciador = new Gerenciador();
    cpuGerenciador = new Gerenciador_cpu();
    memGerenciador = new GerenciadorMem();
    energyGerenciador = new Gerenciador_Energy();


    colorList.push_back(Qt::blue);
    colorList.push_back(Qt::gray);
    colorList.push_back(Qt::red);
    colorList.push_back(Qt::yellow);
    colorList.push_back(Qt::magenta);
    colorList.push_back(Qt::darkBlue);
    colorList.push_back(Qt::cyan);

    //Connecting the signals to their functions
    qRegisterMetaType <QVector<double>>("QVector<double>");
    connect(this, SIGNAL(slotUpdateCpuChart(QVector<double>)), SLOT(updateCpuChart(QVector<double>)) );
    connect(this, SIGNAL(slotUpdateMemChart(double, double)), SLOT(updateMemChart(double, double)) );
    connect(this, SIGNAL(slotUpdateEnergyChart(int)), SLOT(updateEnergyChart(int)) );
    connect(this, SIGNAL(slotUpdateTimeChart(double)), SLOT(updateTimeChart(double)) );

    // Initiating all charts;
    startCpuChart();
    startMemChart();
    startBubbleChart();
    startEnergyChart();
    startTimeChart();

    run();
}

void MainWindow::run(){
    if(isFirst){
        // Initiating threads and delegating their main function
        threadCpu = std::thread(&MainWindow::calculateCpu, this);
        threadMem = std::thread(&MainWindow::calculateMem, this);
        threadEnergy = std::thread(&MainWindow::calculateEnergy, this);
        threadTime = std::thread(&MainWindow::calculateTime, this);
        isFirst = false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setColors()
{
    // Setting a list of usable colors
    colorList.append("red");
    colorList.append("green");
    colorList.append("blue");
    colorList.append("cyan");
    colorList.append("magenta");
    colorList.append("yellow");
    colorList.append("black");

}

void MainWindow::startCpuChart()
{

    for(int i = 0; i < cpuGerenciador->getNCpus(); ++i){
        ui->widget_cpu->addGraph();
        ui->widget_cpu->graph(i)->setName("CPU " + QString::number(i + 1));
        ui->widget_cpu->graph(i)->setPen(QPen(colorList.at(i)));
    }

    ui->widget_cpu->legend->setVisible(true);
    ui->widget_cpu->xAxis->setTickLabels(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->widget_cpu->xAxis->setTicker(timeTicker);
    ui->widget_cpu->axisRect()->setupFullAxesBox();
    ui->widget_cpu->yAxis->setRange(-0.5, 100.5);

    connect(ui->widget_cpu->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_cpu->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::startMemChart()
{
    ui->widget_mem->addGraph();
    ui->widget_mem->graph(0)->setName("Memory");
    ui->widget_mem->graph(0)->setPen(QPen(colorList.at(0)));

    ui->widget_mem->addGraph();
    ui->widget_mem->graph(1)->setName("Swap");
    ui->widget_mem->graph(1)->setPen(QPen(colorList.at(1)));

    ui->widget_mem->legend->setVisible(true);
    ui->widget_mem->xAxis->setTickLabels(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->widget_mem->xAxis->setTicker(timeTicker);
    ui->widget_mem->axisRect()->setupFullAxesBox();
    ui->widget_mem->yAxis->setRange(-0.5, 100.5);

    connect(ui->widget_mem->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_mem->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::startBubbleChart()
{
    procGerenciador->update();

    ui->widget_bubble->load(QUrl::fromLocalFile("/home/yuri-wrlk/build-Process_Manager-Desktop_Qt_5_7_0_GCC_64bit-Release/index.html"));

}

void MainWindow::startEnergyChart()
{
    ui->widget_energy->addGraph();
    ui->widget_energy->graph(0)->setName("Battery Percentage");
    ui->widget_energy->graph(0)->setPen(QPen(colorList.at(0)));

    ui->widget_energy->legend->setVisible(true);
    ui->widget_energy->xAxis->setTickLabels(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->widget_energy->xAxis->setTicker(timeTicker);
    ui->widget_energy->axisRect()->setupFullAxesBox();
    ui->widget_energy->yAxis->setRange(-5.0, 105.0);

    connect(ui->widget_energy->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_energy->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::startTimeChart()
{
    ui->widget_time->addGraph();
    ui->widget_time->graph(0)->setName("Time");
    ui->widget_time->graph(0)->setPen(QPen(colorList.at(0)));

    ui->widget_time->legend->setVisible(true);
    ui->widget_time->xAxis->setTickLabels(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->widget_time->xAxis->setTicker(timeTicker);
    ui->widget_time->axisRect()->setupFullAxesBox();
    ui->widget_time->yAxis->setRange(-0.5, 9.0);

    connect(ui->widget_time->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_time->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_cpu->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::updateCpuChart(QVector<double> cpuPercents)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    for(int i = 0; i < cpuGerenciador->getNCpus(); ++i)
        ui->widget_cpu->graph(i)->addData(key, cpuPercents.at(i));

    ui->widget_cpu->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->widget_cpu->replot();
}

void MainWindow::updateMemChart(double memPercent, double swapPercent)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    ui->widget_mem->graph(0)->addData(key, memPercent);
    ui->widget_mem->graph(1)->addData(key, swapPercent);

    ui->widget_mem->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->widget_mem->replot();
}


void MainWindow::updateEnergyChart(int batteryPercent)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    ui->widget_energy->graph(0)->addData(key, batteryPercent);

    ui->widget_energy->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->widget_energy->replot();
}

void MainWindow::updateTimeChart(double remainingTime)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    ui->widget_time->graph(0)->addData(key, remainingTime);

    ui->widget_time->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->widget_time->replot();
}

void MainWindow::calculateCpu()
{
    QVector<double> cpuValues;
    while(true)
    {
        cpuGerenciador->updateParameters();
        cpuValues = cpuGerenciador->calculateUsage();
        emit(slotUpdateCpuChart(cpuGerenciador->calculateUsage()));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void MainWindow::calculateMem()
{
    while(true)
    {
        memGerenciador->updateData();
        emit(slotUpdateMemChart(memGerenciador->getMemPercent(), memGerenciador->getSwapPercent()));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void MainWindow::calculateEnergy()
{
    while(true)
    {
        energyGerenciador->updateData();
        emit(slotUpdateEnergyChart(energyGerenciador->getBatteryPercent()));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void MainWindow::calculateTime()
{
    while(true)
    {
        double time = (energyGerenciador->getRemainingTimeMin() / 3600);

        emit(slotUpdateTimeChart(time));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


void MainWindow::on_killButton_clicked()
{
    std::string pid = ui->lineEdit->text().toStdString();
    std::stringstream aux;
    aux << "kill -9 " << pid;

    system(aux.str().c_str());
    procGerenciador->update();
    ui->widget_bubble->reload();
}

void MainWindow::on_updateButton_clicked()
{
    std::string filterType = ui->FilterMenu->currentText().toStdString();
    if (filterType == "Filtro por Memória"){
        procGerenciador->setPrintType(Print_parameter::MEM);
    }
    else if(filterType == "Filtro por Nº de Threads"){
        procGerenciador->setPrintType(Print_parameter::THREADS);
    }
    else if(filterType == "Filtro por CPU") {
        procGerenciador->setPrintType(Print_parameter::CPU);
    }

    procGerenciador->update();
    ui->widget_bubble->reload();
}
