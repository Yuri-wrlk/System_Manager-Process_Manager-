#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <thread>
#include "qcustomplot.h"
#include "include_lib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void run();
    void startCpuChart();
    void startMemChart();
    void startBubbleChart();
    void startEnergyChart();
    void startTimeChart();

signals:
    void slotUpdateCpuChart(QVector<double>);
    void slotUpdateMemChart(double, double);
    void slotUpdateEnergyChart(int);
    void slotUpdateTimeChart(double);

public slots:
    void updateCpuChart(QVector<double>);
    void updateMemChart(double, double);
    void updateEnergyChart(int);
    void updateTimeChart(double);

private slots:
    void on_killButton_clicked();
    void on_updateButton_clicked();

private:
    void setColors();
    void calculateCpu();
    void calculateMem();
    void calculateEnergy();
    void calculateTime();

    std::thread threadCpu;
    std::thread threadMem;
    std::thread threadEnergy;
    std::thread threadTime;

    Gerenciador * procGerenciador;
    Gerenciador_cpu * cpuGerenciador;
    GerenciadorMem * memGerenciador;
    Gerenciador_Energy * energyGerenciador;

    bool isFirst = true;
    Ui::MainWindow *ui;
    QTimer dataTimer;
    QVector<QColor> colorList;
};

#endif // MAINWINDOW_H
