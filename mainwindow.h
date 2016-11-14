#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <thread>
#include "qcustomplot.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sortThreads();
    void startCpuChart();
    void startMemChart();
    void startBubbleChart();
    void startEnergyChart();
    void startTimeChart();

signals:
    void slotUpdateCpuChart();
    void slotUpdateMemChart();
    void slotUpdateBubbleChart();
    void slotUpdateEnergyChart();
    void slotUpdateTimeChart();

public slots:
    void updateCpuChart();
    void updateMemChart();
    void updateBubbleChart();
    void updateEnergyChart();
    void updateTimeChart();

private:
    void setColors();
    void calculateCpu();
    void calculateMem();
    void calculateBubble();
    void calculateEnergy();
    void calculateTime();

    std::thread threadCpu;
    std::thread threadMem;
    std::thread threadBubble;
    std::thread threadEnergy;
    std::thread threadTime;

    Ui::MainWindow *ui;
    QTimer dataTimer;
    QVector<QColor> colorList;
};

#endif // MAINWINDOW_H
