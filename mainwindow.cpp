#include "include_lib.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Setting up the UI
    ui->setupUi(this);

    //Setting a list of useable colors
    setColors();

    ui->widget_bubble->load(QUrl::fromLocalFile("/home/Process_Manager/index.html"));

    //Connecting the signals to their functions
    connect(this, SIGNAL(slotUpdateCpuChart()), SLOT(updateCpuChart()) );
    connect(this, SIGNAL(slotUpdateMemChart()), SLOT(updateMemChart()) );
    connect(this, SIGNAL(slotUpdateBubbleChart()), SLOT(updateBubbleChart()) );
    connect(this, SIGNAL(slotUpdateEnergyChart()), SLOT(updateEnergyChart()) );
    connect(this, SIGNAL(slotUpdateTimeChart()), SLOT(updateTimeChart()) );

    // Initiating all charts;
    startCpuChart();
    startMemChart();
    startBubbleChart();
    startEnergyChart();
    startTimeChart();

    sortThreads();


}

void MainWindow::sortThreads(){
    // Initiating threads and delegating their main function
    threadCpu = std::thread(&MainWindow::calculateCpu, this);
    threadMem = std::thread(&MainWindow::calculateMem, this);
    threadBubble = std::thread(&MainWindow::calculateBubble, this);
    threadEnergy = std::thread(&MainWindow::calculateEnergy, this);
    threadTime = std::thread(&MainWindow::calculateTime, this);
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
    ui->widget_cpu->addGraph();

}

void MainWindow::startMemChart()
{

}

void MainWindow::startBubbleChart()
{

}

void MainWindow::startEnergyChart()
{

}

void MainWindow::startTimeChart()
{

}

void MainWindow::updateCpuChart()
{

}

void MainWindow::updateMemChart()
{

}

void MainWindow::updateBubbleChart()
{

}

void MainWindow::updateEnergyChart()
{

}

void MainWindow::updateTimeChart()
{

}

void MainWindow::calculateCpu()
{

}

void MainWindow::calculateMem()
{

}

void MainWindow::calculateBubble()
{

}

void MainWindow::calculateEnergy()
{

}

void MainWindow::calculateTime()
{

}
