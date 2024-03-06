/**
*@file mainwindow.h
*@breif  header file for the mainwindow widget of qt
*@author lusmdl
*@date 06.03.2024
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {

    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

    //navigate through pages

    void enterStartWindow();
    void enterSetupWindow();
    void enterPreperationWindow();
    void enterControlWindow();
    void enterBoardWindow();

};
#endif // MAINWINDOW_H
