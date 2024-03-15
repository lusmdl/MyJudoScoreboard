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
Scoreboard::Scoreboard(QWidget *parent) : QDialog(parent),
    ui(new Ui::Scoreboard),
    scene(new QGraphicsScene(this)),
    graphicsView(new QGraphicsView(scene)) {

    // constructor of scoreboard class

    qDebug() << "Scoreboard::Scoreboard(QWidget *parent)";

    // Initialisiert die Benutzeroberfläche des Scoreboard-Fensters mit den in Qt Designer erstellten Elementen
    ui->setupUi(this);

    // Fenstergröße und -position
    getScreenData();
    this->resize(widthScreen * factorScreen, heightScreen * factorScreen);

    // Erstellen Sie ein neues vertikales Layout und setzen Sie es als Layout des Scoreboard-Dialogs.
    layout = new QVBoxLayout(this);

    // Fügen Sie die QGraphicsView-Komponente, die zur Anzeige von Grafiken verwendet wird, dem Layout hinzu.
    layout->addWidget(graphicsView);

    // Setzen Sie das Layout des Dialogfensters auf das erstellte Layout.
    setLayout(layout);

    // Initialisieren Sie die Grafikansicht, um Grafiken anzuzeigen, und fügen Sie sie dem Layout hinzu.
    initializeGraphic();

    // QTimer initialisieren und starten, um scoreboardLoop() alle 500 Millisekunden aufzurufen
    connect(&scoreboardTimer, &QTimer::timeout, this, &Scoreboard::scoreboardLoop);
    scoreboardTimer.start(500);
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
 *
 * @warning This method is called in the constructor to initialize the graphic elements.
 * @warning This is fine, but be aware that you only need to init the object once, so it is better to perform this operation only once.
 */
void Scoreboard::initializeGraphic() {

    // Diese Methode nur einmal aufrufen!!!

    qDebug() << "Scoreboard::initializeGraphic()";

    getScreenData();
    getWinData();
    getSceneData();
    getGraphicsViewData();

    // Grafikobjekte
    // Hier sollten Sie Ihre Grafikobjekte entsprechend positionieren und skalieren

    // Rechtecke erstellen
    createRects();
    createBlackRect(); // Neues schwarzes Rechteck erstellen
    createDisplay("Fighter One", "Fighter Two");

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// loop
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

void Scoreboard::scoreboardLoop() {

    // Diese Methode wird alle 500 Millisekunden aufgerufen
    // Fügen Sie hier Ihren Code ein, der alle 500 Millisekunden ausgeführt werden soll

    //qDebug() << "Scoreboard::scoreboardLoop()";

    if (isVisible()) {

        // Wenn das Scoreboard sichtbar ist, führen Sie den Code aus

        qDebug() << "Scoreboard is currently visible";

        updateDigits();
        updateDisplay("Louis", "Ich");

    }
    else {

        // Wenn das Scoreboard nicht sichtbar ist, geben Sie eine entsprechende Meldung aus

        //qDebug() << "Scoreboard is currently not visible";
    }
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
// setter
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///


void Scoreboard::setTimer(unsigned int seconds) {

    qDebug() << "Scoreboard::setTimer(unsigned int seconds)";

    secondsTimer = seconds;
    qDebug() << "set seconds to -> " << secondsTimer;
}

/*

void Scoreboard::setNames(QString nameA, QString nameB) {

    qDebug() << "Scoreboard::setNames(QString nameA, QString nameB)";

    upperName = nameA;
    lowerName = nameB;

}
*/

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
    upperRect = new QGraphicsRectItem;
    upperRect = scene->addRect(upperRectBounds, QPen(Qt::NoPen), QBrush(Qt::white));

    // Unten Rechteck erstellen
    lowerRect = new QGraphicsRectItem;
    lowerRect = scene->addRect(lowerRectBounds, QPen(Qt::NoPen), QBrush(Qt::blue));
}

void Scoreboard::createBlackRect() {

    qDebug() << "Scoreboard::createBlackRect()";
    upValueIppon = 100;

    // Parameter für die Größe des schwarzen Rechtecks
    const double rectHeightFactor = 1.0 / 3.0; // Höhe ist ein Drittel der Fenstergröße
    const double rectWidthFactor = 1.5 * rectHeightFactor; // Breite ist 1,5 mal so groß wie die Höhe

    // Berechnung der Größe des Rechtecks
    qreal rectWidth = widthGraph * rectWidthFactor;
    qreal rectHeight = widthGraph * rectHeightFactor;

    // Berechnung der Position des Rechtecks
    qreal rectX = width() - rectWidth; // Rechter Rand des Fensters
    qreal rectY = (height() - rectHeight) / 2; // Horizontale Mittellinie des Fensters

    // Erstellen des schwarzen Rechtecks
    blackRect = new QGraphicsRectItem;
    QRectF rectBounds(rectX, rectY, rectWidth, rectHeight);
    blackRect = scene->addRect(rectBounds, QPen(Qt::NoPen), QBrush(Qt::black));

    // Erstellen des Text-Items für das schwarze Rechteck
    blackRectTextItem = new QGraphicsTextItem;
    blackRectTextItem->setFont(QFont("Arial", rectHeight / 2)); // Die Schriftgröße ist die Hälfte der Rechteckhöhe
    blackRectTextItem->setDefaultTextColor(Qt::yellow); // Gelbe Farbe für den Text
    blackRectTextItem->setPos(rectX + 0.1 * rectWidth, rectY); // Positionierung des Text-Items im Rechteck
    blackRectTextItem->setZValue(1); // Damit der Text über dem Rechteck liegt
    scene->addItem(blackRectTextItem);
}

void Scoreboard::createDisplay(const QString &nameA, const QString &nameB) {

    // Überprüfen, ob die Szene initialisiert ist

    if (scene) {


        // berechne die Schriftgröße
        uint8_t textSize = heightGraph * 0.08;
        qDebug() << "display text hight: " << textSize;

        QFont font(TEXT_STYLE, textSize); // Beispielgröße und Schriftart

        // Text-Item für den ersten Namen erstellen und konfigurieren
        QGraphicsTextItem *upNameTextItem = new QGraphicsTextItem(nameA);
        upNameTextItem->setFont(font);
        upNameTextItem->setDefaultTextColor(Qt::black); // Beispiel Farbe

        // Setzen der Position des ersten Text-Items
        qreal upNameTextHeight = upNameTextItem->boundingRect().height();
        upNameTextItem->setPos(10, 10); // Links oben

        // Hinzufügen des ersten Text-Items zur Szene
        scene->addItem(upNameTextItem);

        // Text-Item für die Anzeige der Integer-Werte erstellen und konfigurieren
        QString upValuesText = QString(POINTS_FORMAT)
                                   .arg(QString("%1").arg(upValueIppon, 3, 10, QChar(' ')))
                                   .arg(QString("%1").arg(upValueWazari, 3, 10, QChar(' ')))
                                   .arg(QString("%1").arg(upValueYuko, 3, 10, QChar(' ')))
                                   .arg(QString("%1").arg(upValueShido, 3, 10, QChar(' ')));
        QGraphicsTextItem *upValuesTextItem = new QGraphicsTextItem(upValuesText);
        upValuesTextItem->setFont(font);
        upValuesTextItem->setDefaultTextColor(Qt::black); // Beispiel Farbe

        // Setzen der Position des Text-Items für die Integer-Werte
        //qreal upValuesTextWidth = upValuesTextItem->boundingRect().width();
        upValuesTextItem->setPos(10, upNameTextItem->pos().y() + upNameTextHeight + 5); // Unterhalb des ersten Text-Items

        // Hinzufügen des Text-Items für die Integer-Werte zur Szene
        scene->addItem(upValuesTextItem);

        // Text-Item für den zweiten Namen erstellen und konfigurieren
        QGraphicsTextItem *downNameTextItem = new QGraphicsTextItem(nameB);
        downNameTextItem->setFont(font);
        downNameTextItem->setDefaultTextColor(Qt::white); // Weiß als Schriftfarbe

        // Setzen der Position des zweiten Text-Items
        qreal downNameTextHeight = downNameTextItem->boundingRect().height();
        downNameTextItem->setPos(10, heightGraphViewPort - downNameTextHeight - 10); // Links unten

        // Hinzufügen des zweiten Text-Items zur Szene
        scene->addItem(downNameTextItem);

        // Text-Item für die Anzeige der Integer-Werte erstellen und konfigurieren
        QString downValuesText = QString(POINTS_FORMAT)
                                     .arg(QString("%1").arg(downValueIppon, 3, 10, QChar(' ')))
                                     .arg(QString("%1").arg(downValueWazari, 3, 10, QChar(' ')))
                                     .arg(QString("%1").arg(downValueYuko, 3, 10, QChar(' ')))
                                     .arg(QString("%1").arg(downValueShido, 3, 10, QChar(' ')));
        QGraphicsTextItem *downValuesTextItem = new QGraphicsTextItem(downValuesText);
        downValuesTextItem->setFont(font);
        downValuesTextItem->setDefaultTextColor(Qt::white); // Beispiel Farbe

        // Setzen der Position des Text-Items für die Integer-Werte
        downValuesTextItem->setPos(10, heightGraphViewPort - downValuesTextItem->boundingRect().height() - downNameTextHeight - 5); // Über dem zweiten Text-Item

        // Hinzufügen des Text-Items für die Integer-Werte zur Szene
        scene->addItem(downValuesTextItem);
    }
    else {
        qDebug() << "Error: Scene is not initialized!";
    }
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

        upperRect->update();
        lowerRect->update();
    }
    else {

        qDebug() << "Error: Rectangles not initialized!";
    }

}

void Scoreboard::updateBlackRect() {

    qDebug() << "Scoreboard::updateBlackRect()";

    // Überprüfen, ob die Objekte bereits initialisiert wurden
    if (blackRect && blackRectTextItem) {

        // Parameter für die Größe des schwarzen Rechtecks aktualisieren
        const double rectHeightFactor = 1.0 / 3.0; // Höhe ist ein Drittel der Fenstergröße
        const double rectWidthFactor = 1.5 * rectHeightFactor; // Breite ist 1,5 mal so groß wie die Höhe

        // Berechnung der Größe des Rechtecks
        qreal rectWidth = width() * rectWidthFactor;
        qreal rectHeight = height() * rectHeightFactor;

        qDebug() << "breite ausgelesen: " << width();

        // Berechnung der Position des Rechtecks
        qreal rectX = width() - rectWidth; // Rechter Rand des Fensters
        qreal rectY = (height() - rectHeight) / 2; // Horizontale Mittellinie des Fensters

        // Aktualisieren der Größe und Position des schwarzen Rechtecks
        blackRect->setRect(rectX, rectY, rectWidth, rectHeight);

        // Aktualisieren der Schriftgröße und Position des Text-Items im schwarzen Rechteck
        blackRectTextItem->setFont(QFont(TEXT_STYLE, rectHeight / 2)); // Die Schriftgröße ist die Hälfte der Rechteckhöhe
        blackRectTextItem->setPos(rectX + 0.1 * rectWidth, rectY); // Positionierung des Text-Items im Rechteck

        blackRect->update();
        blackRectTextItem->update();
    }
    else {

        qDebug() << "Warning: Black rectangle or text item not initialized or already destroyed!";
    }
}



void Scoreboard::updateDigits() {

    qDebug() << "Scoreboard::updateDigits(unsigned int seconds)";

    // Umrechnung der Sekunden in Minuten und Sekunden
    unsigned int minutes = secondsTimer / 60;
    unsigned int remainingSeconds = secondsTimer % 60;

    qDebug() << "calculate timer (" << secondsTimer << " sec): " << minutes << " : " << remainingSeconds;

    // Konvertierung der Minuten und Sekunden in Zeichenfolgen
    QString minutesStr = QString("%1").arg(minutes, 2, 10, QChar('0')); // Führende Nullen für einstellige Minuten hinzufügen
    QString secondsStr = QString("%1").arg(remainingSeconds, 2, 10, QChar('0')); // Führende Nullen für einstellige Sekunden hinzufügen

    // Aktualisierung der Texte für die Ziffern
    QString digitsText = minutesStr + ":" + secondsStr;

    // Setzen des aktualisierten Textes für die Ziffern
    if (blackRectTextItem) {

        blackRectTextItem->setPlainText(digitsText);

        blackRectTextItem->update();
    }
    else {

        qDebug() << "Error: Black rectangle text item not initialized!";
    }
}

void Scoreboard::updateDisplay(const QString &nameA, const QString &nameB) {
    // Suchen und löschen des vorhandenen Namens-Text-Items
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem *item : items) {
        QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
        if (textItem && textItem != blackRectTextItem) { // Sicherstellen, dass es sich nicht um das Ziffern-Text-Item handelt
            scene->removeItem(item);
            delete item;
        }
    }
    // Neuen Namen hinzufügen
    createDisplay(nameA, nameB);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// resize
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///

void Scoreboard::resizeGraphicView() {

    qDebug() << "Scoreboard::resizeGraphicView()";

    getGraphicsViewData();

    // parameter

    //const double factor {1.00};
    const int w =  width();
    const int h = height();

    qDebug() << "calculate new graphicsView size: " << w << " x " << h;

    // Setzen Sie die neue Größe der GraphicsView
    graphicsView->setGeometry(0, 0, w, h);

    // Antialiasing für eine glattere Darstellung aktivieren
    graphicsView->setRenderHint(QPainter::Antialiasing);


    //QRectF sceneRect(0, 0, w, h); // Die Szene sollte die Größe des Fensters haben
    // Die Szene auf die Größe des Fensters setzen
    //scene->setSceneRect(0, 0, w, h);

    //graphicsView->setScene(scene);
    //graphicsView->fitInView(sceneRect, Qt::KeepAspectRatio);
    // Die Grafikansicht aktualisieren, um die Änderungen anzuzeigen
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    // Aktualisieren Sie die Grafikansicht, um die Änderungen anzuzeigen
    graphicsView->update();
}

void Scoreboard::resizeScene() {

    qDebug() << "Scoreboard::resizeScene()";

    getSceneData();

    // parameter

    //const double factor {1.00};
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

    getWinData();

    resizeLayout();
    resizeScene();
    resizeGraphicView();

    // Update the size of rectangles within the scene
    updateRects();
    updateBlackRect();
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


