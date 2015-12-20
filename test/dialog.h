#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <mypixmapitem.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setMyPixmapItem(MyPixmapItem* pixmapItem);

private slots:

    void on_okbt_clicked();

    void on_canclebt_clicked();

private:
    Ui::Dialog *ui;
    MyPixmapItem* pixmapItem;
};

#endif // DIALOG_H
