#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setMyPixmapItem(MyPixmapItem *pixmapItem)
{
    this->pixmapItem = pixmapItem;

    //update threshold value
    this->ui->thresvalue->setValue(this->pixmapItem->getThreshold());
}

void Dialog::on_okbt_clicked()
{
    //update threshold and cut
    this->pixmapItem->setThreshold(this->ui->thresvalue->value());
    this->pixmapItem->cut();

    this->destroy();
}

void Dialog::on_canclebt_clicked()
{
    this->destroy();//do nothing
}
