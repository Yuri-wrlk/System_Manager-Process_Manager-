#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

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
#include "processo.h"
#include "gerenciador_cpu.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

bool read(std::string File, std::vector<Processo>& processList );

#endif // INCLUDE_LIB_H
