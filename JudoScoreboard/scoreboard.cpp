#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QDebug>

Scoreboard::Scoreboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Scoreboard),
    scene(new QGraphicsScene(this)),
    graphicsView(new QGraphicsView(scene)), // Erstellen Sie QGraphicsView
    upperRect(nullptr),
    lowerRect(nullptr) {

    ui->setupUi(this);

    // Erstellen Sie ein vertikales Layout direkt auf dem Dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Fügen Sie QGraphicsView zum Layout hinzu
    layout->addWidget(graphicsView);

    createRects();
}

Scoreboard::~Scoreboard() {
    delete ui;
}

void Scoreboard::createRects() {
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
    int width = graphicsView->width();
    int height = graphicsView->height();

    // Obere Hälfte weiß
    upperRect->setRect(0, 0, width, height / 2);

    // Untere Hälfte blau
    lowerRect->setRect(0, height / 2, width, height / 2);
}


void Scoreboard::resizeEvent(QResizeEvent *event) {
    updateRectsSize();
}

QGraphicsScene* Scoreboard::getScene() const {
    return scene;
}

void Scoreboard::closeBoard() {

    // message to the programmer to check if it´s working
    qDebug() << "close board";

    // trigger signal for the other mainwindow class
    emit deleteBoardPointer();
}
