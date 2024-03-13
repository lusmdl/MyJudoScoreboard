/**
*@file mainwindow.cpp
*@breif  
*@author lusmdl
*@date 06.03.2024
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scoreboard.h"
#include <QDebug>

/**
*@breif  
*@param
*@return
*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    
    // constructor

    qDebug() << "MainWindow constructor called.";
    
    ui->setupUi(this);

    // show only at opening
    enterStartWindow();
}

MainWindow::~MainWindow() {

    // destructor

    // debug information
    qDebug() << "MainWindow destructor called.";
    delete ui;
}

void MainWindow::enterStartWindow() {

    // start window contains some helpfull informations

    qDebug() << "enter Start";

    // open correct page
    int index = 0;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    } 
    else {

        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

void MainWindow::enterSetupWindow() {

    // setup contains all settings and options for the program

    qDebug() << "enter Setup";

    // open correct page
    int index = 1;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    } 
    else {
        
        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

void MainWindow::enterPreperationWindow() {

    // Preparation is the window of opportunity when it comes to the upcoming battles
    // Tournaments, teams and fighters can be managed here

    qDebug() << "enter Preperation";

    // open correct page
    int index = 2;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    } 
    else {
        
        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

void MainWindow::enterControlWindow() {

    // The control page provides everything you need to manage and control the board
    
    qDebug() << "enter Control";

    // open correct page
    int index = 3;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    } else {
        
        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

void MainWindow::enterBoardWindow() {

    // The board is the visualization for the program. Everything boils down to it
    // In the board page, you can open a second window for an additional screen
    // manage the second window

    qDebug() << "enter Board";

    // open correct page
    int index = 4;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    } else {

        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

void MainWindow::generateScoreboard() {

    // generate the Scoreboard

    qDebug() << "open Board";

    // creating object an open window
    board = new Scoreboard(this);
    board->show();

}

