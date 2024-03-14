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

class Scoreboard : public QDialog
{
    Q_OBJECT

    signals:
        void deleteBoardPointer();


    public:
        explicit Scoreboard(QWidget *parent = nullptr);
        ~Scoreboard();

        QGraphicsScene* getScene() const;

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private:
        Ui::Scoreboard *ui;
        QGraphicsScene *scene;
        QGraphicsView *graphicsView;
        QGraphicsRectItem *upperRect;
        QGraphicsRectItem *lowerRect;

        void createRects();
        void updateRectsSize();
        void updateRects();

    private slots:
        void closeBoard();
};

#endif // SCOREBOARD_H
