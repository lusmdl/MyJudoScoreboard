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
#include <QTimer>

/**
*@breif  
*@param
*@return
*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), board(nullptr) {

    // constructor

    qDebug() << "MainWindow constructor called.";

    ui->setupUi(this);

    // show only at opening
    enterStartWindow();

    // Setzen Sie die WindowFlags, um das Hauptfenster über anderen Fenstern zu halten
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}


MainWindow::~MainWindow() {

    // destructor

    // debug information
    qDebug() << "MainWindow destructor called.";

    // Falls das Scoreboard-Objekt existiert, löschen Sie es und setzen Sie den Pointer auf nullptr
    if (board != nullptr) {
        delete board;
        board = nullptr;
    }

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

    qDebug() << "open Board";

    // Erstellen Sie ein neues Scoreboard-Objekt, falls keins vorhanden ist
    if (!board) {

        qDebug() << "generate new board";

        board = new Scoreboard(this);
        board->setWindowFlags(Qt::Tool); // oder Qt::SubWindow, je nach Bedarf
        board->show();

        enableBoardFullScreen();

        // Verbindung des Signals `deleteBoardPointer()` des Scoreboard-Objekts mit der Slot-Funktion `deleteBoardPointer()` der MainWindow-Klasse
        connect(board, &Scoreboard::deleteBoardPointer, this, &MainWindow::deleteBoardPointer);

        // MainWindow aktivieren, um es über dem Scoreboard zu platzieren
        this->raise();
        this->activateWindow();
    }
    else {

        qDebug() << "the board window already exists, it's not necessary to generate a new one";
    }

}



void MainWindow::enableBoardFullScreen() {

    if (ui->_4_checkFullScreen->isChecked()) {

        qDebug() << "enable full screen";

        // Scoreboard im Vollbildmodus anzeigen, nur wenn es bereits erstellt wurde
        if (board != nullptr) {

            board->showFullScreen();
        }
    }
    else {

        qDebug() << "disable full screen";

        // Vollbildmodus beenden und Scoreboard im normalen Modus anzeigen, nur wenn es bereits erstellt wurde
        if (board != nullptr) {

            board->showNormal();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    // Überprüfen, ob die gedrückte Taste die Escape-Taste ist

    if (event->key() == Qt::Key_Escape) {

        // Scoreboard schließen, wenn es geöffnet ist

        if (board != nullptr && board->isVisible()) {

            board->close();
        }
    }

    // Weiterleitung an die Basisimplementierung für andere Tastenereignisse
    QMainWindow::keyPressEvent(event);
}

void MainWindow::deleteBoardPointer() {

    if (board) {

        // Löschen Sie den Board-Pointer, wenn das Scoreboard-Fenster abgelehnt wird

        qDebug() << "delete board pointer";

        delete board;
        board = nullptr;
    }
}
