/**
*@file main.cpp
*@breif
*@author lusmdl
*@date 06.03.2024
*/

#include "mainwindow.h"
#include "scoreboard.h"
#include <QApplication>
#include <QGraphicsView>
#include <QHBoxLayout>

/**
*@breif
*@param
*@return
*/
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    // Hauptfenster erstellen
    MainWindow w;

    // Scoreboard erstellen
    //Scoreboard s;

    w.show();

    return a.exec();
}

