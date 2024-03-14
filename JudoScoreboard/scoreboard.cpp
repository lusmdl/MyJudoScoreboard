#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QDebug>

Scoreboard::Scoreboard(QWidget *parent) : QDialog(parent), ui(new Ui::Scoreboard), scene(new QGraphicsScene(this)), graphicsView(new QGraphicsView(scene)), upperRect(nullptr), lowerRect(nullptr) {

    // constructor of scoreboard class

    qDebug() << "Scoreboard::Scoreboard(QWidget *parent)";

    ui->setupUi(this);

    // Erstellen Sie ein vertikales Layout direkt auf dem Dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Fügen Sie QGraphicsView zum Layout hinzu
    layout->addWidget(graphicsView);

    createRects();

    // connections : signal -> slot

}

Scoreboard::~Scoreboard() {

    qDebug() << "Scoreboard::~Scoreboard()";

    delete ui;
}

void Scoreboard::createRects() {

    qDebug() << "Scoreboard::createRects()";

    int width = graphicsView->width();
    int height = graphicsView->height();

    // Obere Hälfte weiß
    QBrush whiteBrush(Qt::white);
    upperRect = scene->addRect(0, 0, width, height / 2, Qt::NoPen, whiteBrush);

    // Untere Hälfte blau
    QBrush blueBrush(Qt::blue);
    lowerRect = scene->addRect(0, height / 2, width, height / 2, Qt::NoPen, blueBrush);
}

void Scoreboard::updateRectsSize() {

    qDebug() << "Scoreboard::updateRectsSize()";

    int width = graphicsView->width();
    int height = graphicsView->height();

    // Obere Hälfte weiß
    upperRect->setRect(0, 0, width, height / 2);

    // Untere Hälfte blau
    lowerRect->setRect(0, height / 2, width, height / 2);
}


void Scoreboard::resizeEvent(QResizeEvent *event) {

    // Rufen Sie die Basis-Klasse-Methode auf, um das Ereignis zu verarbeiten
    QDialog::resizeEvent(event);

    qDebug() << "Scoreboard::resizeEvent(QResizeEvent *event)";

    updateRectsSize();

    // Übergeben Sie die gesamte Szene und verwenden Sie die Option Qt::KeepAspectRatio,
    // um sicherzustellen, dass die Grafik proportional skaliert wird.
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

QGraphicsScene* Scoreboard::getScene() const {

    qDebug() << "Scoreboard::getScene()";

    return scene;
}

void Scoreboard::closeBoard() {

    qDebug() << "Scoreboard::closeBoard()";

    // trigger signal for the other mainwindow class
    emit deleteBoardPointer();
}


