/**
*@file main.cpp
*@breif  
*@author lusmdl
*@date 06.03.2024
*/

#include "mainwindow.h"
#include <QApplication>

/**
*@breif  
*@param
*@return
*/
int main(int argc, char *argv[]) {

    // main funktion
    
    QApplication a(argc, argv);

    // main window
    MainWindow w;
    w.show();

    return a.exec();
}
