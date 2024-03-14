#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QCloseEvent>
#include <QVBoxLayout>


namespace Ui {

    class Scoreboard;
}

class Scoreboard : public QDialog {

    Q_OBJECT

    public:

        // constructor & destructor

        explicit Scoreboard(QWidget *parent = nullptr);
        ~Scoreboard();

        QGraphicsScene* getScene() const;

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

        // screen data

        int widthScreen;
        int heightScreen;
        const double factorScreen {0.5};

        // window data

        int widthWin;
        int heightWin;

        // graphic view data

        int widthGraph;
        int heightGraph;

        int widthGraphViewPort;
        int heightGraphViewPort;

        // scene data

        qreal widthScene;
        qreal heightScene;

        // getter

        void getScreenData();
        void getWinData();
        void getGraphicsViewData();
        void getSceneData();

        // setter

        void initializeGraphic();

        void createRects();

        void updateRects();

        // resize

        void resizeGraphicView();
        void resizeScene();
        void resizeLayout();

    signals:

        void deleteBoardPointer();


    private slots:

        void closeBoard();
};

#endif // SCOREBOARD_H
