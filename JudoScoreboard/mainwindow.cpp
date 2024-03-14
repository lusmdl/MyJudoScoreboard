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
 * @brief Constructor for MainWindow class.
 *
 * @param parent Pointer to the parent widget.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), board(nullptr) {

    // constructor

    qDebug() << "MainWindow::MainWindow(QWidget *parent)";

    // Call setupUi function to initialize the user interface components
    ui->setupUi(this);

    // show only at opening
    enterStartWindow();

    // Setzen Sie die WindowFlags, um das Hauptfenster über anderen Fenstern zu halten
    //setWindowFlags(windowFlags());
}

/**
 * @brief Destructor for MainWindow class.
 *
 * This destructor is responsible for cleaning up resources allocated by MainWindow objects.
 *
 * @note If the Scoreboard object exists, it will be deleted and the pointer will be set to nullptr.
 */
MainWindow::~MainWindow() {

    // destructor

    // debug information
    qDebug() << "MainWindow::~MainWindow()";

    // Falls das Scoreboard-Objekt existiert, löschen Sie es und setzen Sie den Pointer auf nullptr
    if (board != nullptr) {

        delete board;
        board = nullptr;
    }

    delete ui;
}

/**
 * @brief Switches the stacked widget to display the start window.
 *
 * This method sets up the start window and displays it by setting the appropriate index in the stacked widget.
 *
 * The start window typically contains helpful information.
 */
void MainWindow::enterStartWindow() {

    // start window contains some helpfull informations

    qDebug() << "MainWindow::enterStartWindow()";

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

/**
 * @brief Switches the stacked widget to display the setup window.
 *
 * This method sets up the setup window and displays it by setting the appropriate index in the stacked widget.
 *
 * The setup window typically contains all settings and options for the program.
 */
void MainWindow::enterSetupWindow() {

    // setup contains all settings and options for the program

    qDebug() << "MainWindow::enterSetupWindow()";

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

    qDebug() << "MainWindow::enterPreperationWindow()";

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

/**
 * @brief Switches the stacked widget to display the preparation window.
 *
 * This method sets up the preparation window and displays it by setting the appropriate index in the stacked widget.
 *
 * The preparation window is where tournaments, teams, and fighters can be managed in preparation for upcoming battles.
 */
void MainWindow::enterControlWindow() {

    // The control page provides everything you need to manage and control the board
    
    qDebug() << "MainWindow::enterControlWindow()";

    // open correct page
    int index = 3;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    }
    else {
        
        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

/**
 * @brief Switches the stacked widget to display the board window.
 *
 * This method sets up the board window and displays it by setting the appropriate index in the stacked widget.
 *
 * The board window serves as the visualization for the program, where everything comes together.
 * In this window, you can open a second window for an additional screen and manage it.
 */
void MainWindow::enterBoardWindow() {

    // The board is the visualization for the program. Everything boils down to it
    // In the board page, you can open a second window for an additional screen
    // manage the second window

    qDebug() << "MainWindow::enterBoardWindow()";

    // open correct page
    int index = 4;
    if (index != -1) {
        
        // show page
        ui->stackedWidget->setCurrentIndex(index);
    }
    else {

        // invalid page
        
        qDebug() << "Object not found in stackedWidget.";
    }
}

/**
 * @brief Generates and displays the scoreboard window.
 *
 * This method creates a new scoreboard window if one does not already exist.
 * The scoreboard window displays scores and related information.
 *
 * If a scoreboard window already exists, this method does nothing.
 */
void MainWindow::generateScoreboard() {

    qDebug() << "MainWindow::generateScoreboard()";

    if (!board) {

        // Erstellen Sie ein neues Scoreboard-Objekt, falls keins vorhanden ist

        qDebug() << "generate new board";

        // Erstellen Sie ein neues Scoreboard-Objekt und weisen Sie es der Variable `board` zu
        board = new Scoreboard(this);

        // Setzen Sie die Fenstereigenschaften des Scoreboard-Objekts
        // Qt::Dialog: Das Fenster wird als Modal-Dialog behandelt, was bedeutet, dass es den Fokus behält und andere Fenster blockiert, bis es geschlossen wird.
        // Qt::CustomizeWindowHint: Dieses Flag ermöglicht es, benutzerdefinierte Fensterfunktionen festzulegen, z.B. das Hinzufügen von Schaltflächen oder das Ändern des Fensterrahmens.
        // Qt::WindowTitleHint: Zeigt den Fenstertitel an, wenn dieser festgelegt ist.
        // Qt::WindowCloseButtonHint: Zeigt die Schließen-Schaltfläche im Fenster an, damit der Benutzer das Fenster schließen kann.
        // Qt::MSWindowsFixedSizeDialogHint: Verhindert, dass das Fenster seine Größe ändert, wenn der Benutzer versucht, es zu ändern. Diese Funktion ist spezifisch für Windows.
        board->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
        board->setWindowTitle("Scoreboard");

        // Setzen Sie die feste Größe des Scoreboard-Fensters auf die Bildschirmgröße multipliziert mit einem Faktor.
        // Dies stellt sicher, dass das Scoreboard-Fenster die richtige Größe hat und alle Inhalte sichtbar sind.
        //board->setFixedSize(widthScreen * factorScreen, heightScreen * factorScreen);

        // Zeigen Sie das Scoreboard-Fenster an.
        // Diese Methode macht das Scoreboard-Fenster sichtbar und ermöglicht es dem Benutzer, mit ihm zu interagieren.
        board->show();

        // Setzen Sie den Bildmodus für das Scoreboard-Fenster.
        setBoardScreenMode();

        // Verbindung des Signals `deleteBoardPointer()` des Scoreboard-Objekts mit der Slot-Funktion `deleteBoardPointer()` der MainWindow-Klasse
        connect(board, &Scoreboard::deleteBoardPointer, this, &MainWindow::deleteBoardPointer);
    }
    else {

        qDebug() << "the board window already exists, it's not necessary to generate a new one";
    }
}

/**
 * @brief Sets the screen mode for the scoreboard window.
 *
 * This method adjusts the display mode of the scoreboard window based on the user's preference.
 * If the "Full Screen" option is checked, the scoreboard window is displayed in full screen mode.
 * If the "Full Screen" option is unchecked, the scoreboard window is displayed in normal mode.
 */
void MainWindow::setBoardScreenMode() {

    qDebug() << "MainWindow::setBoardScreenMode()";

    if (ui->_4_checkFullScreen->isChecked()) {

        qDebug() << "check full screen";

        if (board != nullptr) {

            // Scoreboard im Vollbildmodus anzeigen, nur wenn es bereits erstellt wurde

            qDebug() << "set window to full screen";

            board->showFullScreen();
        }
    }
    else {

        qDebug() << "uncheck full screen";

        if (board != nullptr) {

            // Vollbildmodus beenden und Scoreboard im normalen Modus anzeigen, nur wenn es bereits erstellt wurde

            qDebug() << "set window back to normal";

            board->showNormal();
        }
    }
}

/**
 * @brief Handles key press events for the main window.
 *
 * This method is called when a key is pressed while the main window has focus.
 * It checks if the pressed key is the Escape key and closes the scoreboard window if it is open.
 * All other key press events are forwarded to the base implementation.
 *
 * @param event A pointer to the QKeyEvent object representing the key press event.
 */
void MainWindow::keyPressEvent(QKeyEvent *event) {

    qDebug() << "MainWindow::keyPressEvent(QKeyEvent *event)";


    if (event->key() == Qt::Key_Escape) {

        // Scoreboard schließen, wenn es geöffnet ist

        qDebug() << "Key_Escape pressed";

        if (board != nullptr && board->isVisible()) {

            board->close();
        }
    }

    // Weiterleitung an die Basisimplementierung für andere Tastenereignisse
    QMainWindow::keyPressEvent(event);
}

/**
 * @brief Deletes the pointer to the scoreboard window.
 *
 * This method is called when the scoreboard window is closed or rejected.
 * It deletes the scoreboard window object and sets the pointer to nullptr.
 *
 * This ensures proper cleanup of resources and prevents memory leaks.
 */
void MainWindow::deleteBoardPointer() {

    qDebug() << "MainWindow::deleteBoardPointer()";

    if (board) {

        // Löschen Sie den Board-Pointer, wenn das Scoreboard-Fenster rejected wird

        delete board;
        board = nullptr;
        qDebug() << "pointer gelöscht";
    }
}
