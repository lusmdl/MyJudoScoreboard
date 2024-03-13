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
    Scoreboard s;

    // GraphicsView erstellen
    QGraphicsView *graphicsView = new QGraphicsView;
    graphicsView->setScene(s.getScene()); // Setzen Sie die Szene des GraphicsView auf die Szene des Scoreboards

    // Horizontales Layout erstellen
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(graphicsView); // GraphicsView zum Layout hinzufügen
    w.setLayout(layout); // Layout zum Hauptfenster setzen

    w.show();

    return a.exec();
}

