#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include "mypixmapitem.h"
#include "myrectitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionZoom_triggered();

    void on_actionRotate_triggered();

    void on_actionHelp_triggered();

    void on_actionQuit_triggered();

    void on_actionUp_triggered();

    void on_actionDowm_triggered();

    void on_actionCut_triggered();

    void on_actionDelete_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    MyPixmapItem* pixmapItem;
    MyPixmapItem* selectedItem;

    void open();//openImage
    void save();//save image
    void updateSelectedItem();



};

#endif // MAINWINDOW_H
