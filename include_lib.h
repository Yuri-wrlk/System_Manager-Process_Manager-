#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

enum Print_parameter {THREADS, CPU, MEM} ;

#include <QApplication>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <thread>
#include <QVector>
#include <QFile>
#include <QHash>
#include <QMainWindow>
#include <QTimer>
#include <chrono>
#include "qcustomplot.h"
#include "processo.h"
#include "gerenciador_cpu.h"
#include "gerenciador_mem.h"
#include "gerenciador_energy.h"
#include "gerenciador.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

bool read(std::string File, std::vector<Processo>& processList );


#endif // INCLUDE_LIB_H
