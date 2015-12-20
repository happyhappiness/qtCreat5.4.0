#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include "dialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initialize scene
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    pixmapItem = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
    if(scene != NULL)
        delete scene;
    if(pixmapItem != NULL)
        delete pixmapItem;
}


void MainWindow::on_actionOpen_triggered()
{
    open();
}


void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionZoom_triggered()
{
    updateSelectedItem();
    if(selectedItem != NULL)
        selectedItem->setMode(false);
}//move

void MainWindow::on_actionRotate_triggered()
{
    updateSelectedItem();
    if(selectedItem != NULL)
        selectedItem->setMode(true);
}//rotate

void MainWindow::on_actionHelp_triggered()
{
      QMessageBox::question(this, "提示", " Ctrl + M : 切换模式 \n Up : 上移图层\n Down : 下移图片\n"
                        " Delete : 删除图片 \n C : 圆形裁剪", QMessageBox::Close);
}//help menu: show help text


void MainWindow::on_actionQuit_triggered()
{
    int choose = QMessageBox::question(this,"警告", "确认退出系统吗？",
                                       QMessageBox::Ok, QMessageBox::Cancel);
    if(choose == QMessageBox::Ok)
    {
        this->destroy();
    }
}//close the window

void MainWindow::on_actionUp_triggered()
{
    updateSelectedItem();
    if(selectedItem != NULL)
        selectedItem->upLevel();
}//up Move the image

void MainWindow::on_actionDowm_triggered()
{
    updateSelectedItem();
    if(selectedItem != NULL)
        selectedItem->downLevel();
}//down move the image


void MainWindow::on_actionCut_triggered()
{

    //find the pixmapItem selected and cut it
    updateSelectedItem();
    if(this->selectedItem != NULL)
    {
        Dialog* dialog = new Dialog();
        dialog->setMyPixmapItem(this->selectedItem);
        dialog->setModal(Qt::ApplicationModal);
        dialog->show();
    }

}//cut and open another dialog to specify the threshold


void MainWindow::on_actionDelete_triggered()
{
    updateSelectedItem();
    if(this->selectedItem != NULL)
    {
        this->ui->graphicsView->scene()->removeItem(selectedItem);
    }

}//delete the pixmapItem that was chosed


void MainWindow::open()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("打开图片"), " ", tr( "Image Files(*.bmp *.jpg *.png *.jpeg)"));
    if(fileNames.empty())
    {
        QMessageBox::warning(this, "警告", "请选择文件");
        return;
    }
    QStringListIterator fileNameIterator(fileNames);
    QString fileName;
    while (fileNameIterator.hasNext())
    {
        fileName = fileNameIterator.next();
        if(fileName != NULL)
        {
            //image
            pixmapItem = new MyPixmapItem();
            QPixmap pixmap = QPixmap(fileName);
            pixmapItem->setPixmap_o(pixmap);

            scene->addItem(pixmapItem);

        }//show the image in 0, 0
    }
}//open menu: open an image

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存图片"), " ", tr( "Image Files(*.bmp *.jpg *.png *.jpeg)"));
    if(fileName != NULL)
    {
        QPixmap pixmap = ui->graphicsView->grab();
        pixmap.save(fileName);
        QMessageBox::information(this, "通知", "文件保存成功");
    }
}//save menu: save the screencut

void MainWindow::updateSelectedItem()
{
    QList<QGraphicsItem*> items = ui->graphicsView->scene()->selectedItems();
    if(!items.isEmpty())
    {
        this->selectedItem = dynamic_cast<MyPixmapItem*>(items.first());
    }
}

