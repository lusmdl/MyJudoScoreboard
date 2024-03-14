#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QDebug>

/**
 * @brief Constructor for the Scoreboard class.
 *
 * This constructor initializes a Scoreboard object with the specified parent widget.
 * It sets up the user interface, graphics scene, and graphics view for displaying the scoreboard.
 *
 * @param parent Pointer to the parent widget.
 */
Scoreboard::Scoreboard(QWidget *parent) : QDialog(parent), ui(new Ui::Scoreboard), scene(new QGraphicsScene(this)), graphicsView(new QGraphicsView(scene)), upperRect(nullptr), lowerRect(nullptr) {

    // constructor of scoreboard class

    qDebug() << "Scoreboard::Scoreboard(QWidget *parent)";

    getScreenData();

    // Initialisiert die Benutzeroberfläche des Scoreboard-Fensters mit den in Qt Designer erstellten Elementen
    ui->setupUi(this);

    // Fenstergröße und -position
    this->resize(widthScreen * factorScreen, heightScreen * factorScreen);

    // Erstellen Sie ein neues vertikales Layout und setzen Sie es als Layout des Scoreboard-Dialogs.
    layout = new QVBoxLayout(this);

    // Initialisieren Sie die Grafikansicht, um Grafiken anzuzeigen, und fügen Sie sie dem Layout hinzu.
    initializeGraphic();
}

/**
 * @brief Destructor for the Scoreboard class.
 *
 * This destructor cleans up resources allocated by the Scoreboard object.
 * It deletes the user interface object to free up memory.
 */
Scoreboard::~Scoreboard() {

    qDebug() << "Scoreboard::~Scoreboard()";

    delete ui;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialize
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

/**
 * @brief Initializes the graphics view.
 *
 * This method is called when the scoreboard window is displayed and has a size.
 * It retrieves the size of the graphics view and initializes the creation of rectangles for display.
 */
void Scoreboard::initializeGraphic() {

    // Diese Methode wird aufgerufen, sobald das Fenster angezeigt wird und eine Größe hat

    qDebug() << "Scoreboard::initializeGraphicsView()";

    // Fügen Sie die QGraphicsView-Komponente, die zur Anzeige von Grafiken verwendet wird, dem Layout hinzu.
    layout->addWidget(graphicsView);

    // Setzen Sie das Layout des Dialogfensters auf das erstellte Layout.
    setLayout(layout);

    // Grafikobjekte
    // Hier sollten Sie Ihre Grafikobjekte entsprechend positionieren und skalieren

    // Rechtecke erstellen
    createRects();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// getter
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///



void Scoreboard::getScreenData() {

    qDebug() << "Scoreboard::getScreenData()";

    // Zugriff auf den primären Bildschirm
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    if (primaryScreen) {

        // Abrufen der Auflösung des primären Bildschirms

        QRect screenGeometry = primaryScreen->geometry();
        widthScreen = screenGeometry.width();
        heightScreen = screenGeometry.height();

        // Ausgabe der Bildschirmauflösung
        qDebug() << "size screen: " << widthScreen << " x " << heightScreen;
    }
    else {

        // Fehlermeldung, wenn der primäre Bildschirm nicht verfügbar ist
        qDebug() << "Failed to access primary screen.";
    }
}

/**
 * @brief Retrieves data about the current scene.
 *
 * This method extracts the width and height of the scene's bounding rectangle using the sceneRect() method of the QGraphicsScene class.
 * The extracted width and height values are stored in the corresponding member variables of the Scoreboard class.
 * Additionally, debug messages are outputted to the console to display the width and height of the scene.
 */
void Scoreboard::getSceneData() {

    widthScene = scene->width();
    heightScene = scene->height();

    qDebug() << "size scene: " << widthScene << " x " << heightScene;
}

/**
 * @brief Reads the current window data.
 *
 * This method reads the width and height of the dialog window and stores them
 * in the corresponding member variables of the Scoreboard class.
 */
void Scoreboard::getWinData() {

    qDebug() << "Scoreboard::getWinData()";

    // lese die fensterdaten aus

    widthWin = this->width();   // Aktuelle Breite des Dialogfensters
    heightWin = this->height(); // Aktuelle Höhe des Dialogfensters

    qDebug() << "size window: " << widthWin << " x " << heightWin;
}

/**
 * @brief Retrieves the current size of the QGraphicsView.
 *
 * This method retrieves the width and height of the QGraphicsView used to display the scene.
 * The size values are stored in the corresponding member variables of the Scoreboard class.
 */
void Scoreboard::getGraphicsViewData() {

    qDebug() << "Scoreboard::getGraphicsViewData()";

    // graphicsView->width():
    // Diese Methode gibt die Breite der QGraphicsView selbst zurück, unabhängig von der Größe des Viewports oder anderer Eigenschaften.
    // Es gibt die tatsächliche Breite des Grafikbereichs an, ohne Rücksicht auf etwaige Schiebebalken oder Rahmen, die möglicherweise vorhanden sind.
    widthGraph = graphicsView->width();

    heightGraph = graphicsView->height();

    qDebug() << "size graphicView: " << widthGraph << " x " << heightGraph;

    // graphicsView->viewport()->width():
    // Diese Methode gibt die Breite des Viewports zurück, der innerhalb der QGraphicsView liegt. Der Viewport ist der sichtbare Bereich innerhalb der QGraphicsView,
    // in dem die Szene tatsächlich gerendert wird. Die Viewport-Breite kann kleiner sein als die tatsächliche Breite der QGraphicsView,
    // wenn Schiebebalken vorhanden sind oder wenn die Szene größer ist als der sichtbare Bereich.
    widthGraphViewPort = graphicsView->viewport()->width();

    heightGraphViewPort = graphicsView->viewport()->height();

    qDebug() << "size graphicViewPort: " << widthGraphViewPort << " x " << heightGraphViewPort;

    // In vielen Fällen, insbesondere wenn keine Schiebebalken verwendet werden, können beide Methoden die gleiche Breite zurückgeben.
    // Jedoch, wenn Schiebebalken vorhanden sind und die Szene größer ist als der sichtbare Bereich, wird graphicsView->width() die Breite der gesamten QGraphicsView zurückgeben,
    // während graphicsView->viewport()->width() die Breite des sichtbaren Bereichs innerhalb der QGraphicsView zurückgeben wird.
}


/**
 * @brief Retrieves the QGraphicsScene associated with the scoreboard.
 *
 * This method returns a pointer to the QGraphicsScene object that is associated with the scoreboard.
 * Debug message is outputted to the console to indicate the execution of this method.
 *
 * @return A pointer to the QGraphicsScene object associated with the scoreboard, or nullptr if no scene is associated.
 */
QGraphicsScene* Scoreboard::getScene() const {

    qDebug() << "Scoreboard::getScene()";

    if (scene) {

        return scene;
    }
    else {

        qDebug() << "Error: No scene associated with the scoreboard!";
        return nullptr;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// create forms
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

/**
 * @brief Creates rectangles in the scene.
 *
 * This method creates two rectangles within the scene: one for the upper half and one for the lower half.
 * The upper rectangle is colored white, and the lower rectangle is colored blue.
 * The rectangles are added to the scene using the addRect() method of the QGraphicsScene class.
 * The width and height of the rectangles are based on the scene size, respectively.
 */
void Scoreboard::createRects() {

    qDebug() << "Scoreboard::createRects()";

    getGraphicsViewData();

    // Neue Größe der Rechtecke berechnen
    qreal w = widthGraph;
    qreal h = heightGraph / 2; // Teilen Sie die Höhe durch 2 für die obere und untere Hälfte

    // Rechtecke für die obere und untere Hälfte der Szene erstellen
    QRectF upperRectBounds(0, 0, w, h);
    QRectF lowerRectBounds(0, h, w, h);

    // Oben Rechteck erstellen
    upperRect = scene->addRect(upperRectBounds, QPen(Qt::NoPen), QBrush(Qt::white));

    // Unten Rechteck erstellen
    lowerRect = scene->addRect(lowerRectBounds, QPen(Qt::NoPen), QBrush(Qt::blue));
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// update
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

void Scoreboard::updateRects() {

    qDebug() << "Scoreboard::updateRects()";

    getGraphicsViewData();

    // Neue Größe der Rechtecke berechnen
    qreal w = widthGraph;
    qreal h = heightGraph / 2; // Teilen Sie die Höhe durch 2 für die obere und untere Hälfte

    qDebug() << "calculate knew Rects size: " << w << " x " << h;

    if (upperRect && lowerRect) {

        // Obere und untere Rechtecke aktualisieren

        upperRect->setRect(0, 0, w, h);
        lowerRect->setRect(0, h, w, h);
    }
    else {

        qDebug() << "Error: Rectangles not initialized!";
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// resize
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

void Scoreboard::resizeGraphicView() {

    qDebug() << "Scoreboard::resizeGraphicView()";

    // parameter

    const double factor {1.00};
    const int w =  width();
    const int h = height();

    qDebug() << "calculate new graphicsView size: " << w << " x " << h;

    // Setzen Sie die neue Größe der GraphicsView
    graphicsView->setGeometry(0, 0, w, h);

    // Antialiasing für eine glattere Darstellung aktivieren
    graphicsView->setRenderHint(QPainter::Antialiasing);


    //QRectF sceneRect(0, 0, w, h); // Die Szene sollte die Größe des Fensters haben
    // Die Szene auf die Größe des Fensters setzen
    scene->setSceneRect(0, 0, w, h);

    //graphicsView->setScene(scene);
    //graphicsView->fitInView(sceneRect, Qt::KeepAspectRatio);
    // Die Grafikansicht aktualisieren, um die Änderungen anzuzeigen
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    // Aktualisieren Sie die Grafikansicht, um die Änderungen anzuzeigen
    graphicsView->update();
}

void Scoreboard::resizeScene() {

    qDebug() << "Scoreboard::resizeScene()";

    //getWinData();

    // parameter

    const double factor {1.00};
    const int w = width();
    const int h = height();

    //QRectF sceneRect(0, 0, w, g); // Die Szene sollte die Größe des Fensters haben
    //scene->setSceneRect(sceneRect);
    // Die Szene auf die Größe des Fensters setzen
    scene->setSceneRect(0, 0, w, h);

    // Aktualisieren Sie die Szene, um die Änderungen anzuzeigen
    scene->update();
}

void Scoreboard::resizeLayout() {

    // Die Methode ist nicht erforderlich, da das Layout automatisch die Größe des Dialogfensters anpasst.
    // Sie können diese Methode entfernen.

    /*
    qDebug() << "Scoreboard::resizeLayout()";

    getWinData();

    // parameter

    const double factor {1.00};
    const int width = (int) (widthWin * factor);
    const int height = (int) (heightWin * factor);

    // Passen Sie das Layout an die neue Fenstergröße an (falls erforderlich)
    QRect layoutRect(0, 0, width, height);
    layout->setGeometry(layoutRect);

    // Oder aktualisieren Sie das Layout, wenn es sich automatisch anpasst.
    layout->update();
    */
}


/**
 * @brief Handles resize events for the scoreboard dialog.
 *
 * This method is called whenever the scoreboard dialog is resized. It processes the resize event by calling the base class method,
 * and then performs additional tasks related to resizing the scene, resizing the graphics view, and updating the size of rectangles within the scene.
 * Debug messages are outputted to the console to indicate the execution of this method.
 *
 * @param event A pointer to the resize event object containing information about the resize event.
 */
void Scoreboard::resizeEvent(QResizeEvent *event) {

    qDebug() << "Scoreboard::resizeEvent(QResizeEvent *event)";

    // Call the base class method to handle the event
    QDialog::resizeEvent(event);

    resizeLayout();
    resizeGraphicView();
    resizeScene();

    // Update the size of rectangles within the scene
    updateRects();

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// close
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

/**
 * @brief Closes the scoreboard.
 *
 * This method is called to close the scoreboard. It emits a signal `deleteBoardPointer()` to notify the main window class
 * that the scoreboard is being closed.
 * Debug message is outputted to the console to indicate the execution of this method.
 */
void Scoreboard::closeBoard() {

    qDebug() << "Scoreboard::closeBoard()";

    // trigger signal for the other mainwindow class
    emit deleteBoardPointer();
}


