#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QTimer>


#define POINTS_FORMAT "I%1   W%2   Y%3   S%4"
#define TEXT_STYLE  "Consolas"


namespace Ui {

    class Scoreboard;
}

class Scoreboard : public QDialog {

    Q_OBJECT

    public:

        // constructor & destructor

        explicit Scoreboard(QWidget *parent = nullptr);
        ~Scoreboard();

        // pionter

        QGraphicsScene* getScene() const;

        // setter

        void setTimer(unsigned int seconds);
        //void setNames(QString nameA, QString nameB);


    protected:

        void resizeEvent(QResizeEvent *event) override;

    private:

        // pointer

        Ui::Scoreboard *ui;
        QVBoxLayout *layout;
        QGraphicsScene *scene;
        QGraphicsView *graphicsView;
        QGraphicsRectItem *upperRect;
        QGraphicsRectItem *lowerRect;
        QGraphicsRectItem *blackRect;
        QGraphicsTextItem *blackRectTextItem;


        // screen data

        uint16_t widthScreen;
        uint16_t heightScreen;
        const float factorScreen {0.5};

        // window data

        uint16_t widthWin;
        uint16_t heightWin;

        // graphic view data

        uint16_t widthGraph;
        uint16_t heightGraph;

        uint16_t widthGraphViewPort;
        uint16_t heightGraphViewPort;

        // scene data

        qreal widthScene;
        qreal heightScene;

        // timer/counter data

        unsigned int secondsTimer;

        // fighter data

        //QString upperName;
        //QString lowerName;

        uint8_t upValueIppon;
        uint8_t upValueWazari;
        uint8_t upValueYuko;
        uint8_t upValueShido;

        uint8_t downValueIppon;
        uint8_t downValueWazari;
        uint8_t downValueYuko;
        uint8_t downValueShido;

        QTimer scoreboardTimer;

        // getter

        void getScreenData();
        void getWinData();
        void getGraphicsViewData();
        void getSceneData();

        // setter

        void initializeGraphic();

        void createRects();
        void createBlackRect();
        void createDisplay(const QString &nameA, const QString &nameB);
        void updateDisplay(const QString &nameA, const QString &nameB);

        void updateRects();
        void updateBlackRect();
        void updateDigits();

        // resize

        void resizeGraphicView();
        void resizeScene();
        void resizeLayout();


    signals:

        void deleteBoardPointer();


    private slots:

        void closeBoard();
        void scoreboardLoop();
};

#endif // SCOREBOARD_H
