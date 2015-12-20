#include "mypixmapitem.h"
#include <QGraphicsScene>

MyPixmapItem::MyPixmapItem()
{
   //member initialize
    pixmapItem = new QGraphicsPixmapItem();
    pixmapItem->setParentItem(this);


    trRect = new MyRectItem();
    trRect->setParentItem(this);
    blRect = new MyRectItem();
    blRect->setParentItem(this);
    tlRect = new TLRectItem();
    tlRect->setParentItem(this);
    brRect = new TLRectItem();
    brRect->setParentItem(this);
    clRect = new CLRectItem();
    clRect->setParentItem(this);
    crRect = new CLRectItem();
    crRect->setParentItem(this);
    tRect = new TRectItem();
    tRect->setParentItem(this);
    bRect = new TRectItem();
    bRect->setParentItem(this);
    cRect = new CRectItem();
    cRect->setParentItem(this);


    //event
    this->setFlags(ItemIsMovable|ItemIsFocusable|ItemIsSelectable);
   // cutted = true;

    //cut by default
    threshold_value = 50;
}

MyPixmapItem::~MyPixmapItem()
{
    if(pixmapItem != NULL)
        delete pixmapItem;
    if(trRect != NULL)
        delete trRect;
    if(blRect != NULL)
        delete blRect;
    if(tlRect != NULL)
        delete tlRect;
    if(brRect != NULL)
        delete brRect;
    if(clRect != NULL)
        delete clRect;
    if(crRect != NULL)
        delete crRect;
    if(tRect != NULL)
        delete tRect;
    if(bRect != NULL)
        delete bRect;
    if(cRect != NULL)
        delete cRect;
}

QRectF MyPixmapItem::boundingRect() const
{

    int w = trRect->getWidth();
    return QRectF(-w/2, -w/2, pixmap.width() + w, pixmap.height() + w);
}

void MyPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //antialiasing
    painter->setRenderHint(QPainter::Antialiasing);

    pixmapItem->setPixmap(pixmap);
    pixmapItem->paint(painter, option, widget);

    trRect->setOpacity(0);
    blRect->setOpacity(0);
    tlRect->setOpacity(0);
    brRect->setOpacity(0);
    clRect->setOpacity(0);
    crRect->setOpacity(0);
    tRect->setOpacity(0);
    bRect->setOpacity(0);
    cRect->setOpacity(0);

    if(hasFocus())
    {
        painter->setPen(Qt::DashLine);
        painter->drawRect(QRectF(0,0, pixmap.width(), pixmap.height()));
        trRect->setOpacity(1);//keep focus
        blRect->setOpacity(1);//keep focus
        tlRect->setOpacity(1);
        brRect->setOpacity(1);
        clRect->setOpacity(1);
        crRect->setOpacity(1);
        tRect->setOpacity(1);
        bRect->setOpacity(1);
        cRect->setOpacity(1);
    }//control rect

}//paint children

void MyPixmapItem::setPixmap_o(const QPixmap &pixmap_o)
{
    this->pixmap_o = QPixmap(pixmap_o);
    this->setPixmap(pixmap_o);

    //cut
    this->cut();
}//set the original pixmap for cutting change when the pixmapItem was created

QPointF MyPixmapItem::getCenter()
{
    return cRect->pos();
}//return the transformation center

void MyPixmapItem::updateMode()
{
    trRect->updateMode();
    blRect->updateMode();
    tlRect->updateMode();
    brRect->updateMode();
    clRect->updateMode();
    crRect->updateMode();
    tRect->updateMode();
    bRect->updateMode();
}//change mode to the opposite one

void MyPixmapItem::setMode(bool mode)
{
    trRect->setMode(mode);
    blRect->setMode(mode);
    tlRect->setMode(mode);
    brRect->setMode(mode);
    clRect->setMode(mode);
    crRect->setMode(mode);
    tRect->setMode(mode);
    bRect->setMode(mode);
}//set mode to mode


void MyPixmapItem::upLevel()
{
    this->setZValue(this->zValue() + 1);
}//uplevel

void MyPixmapItem::downLevel()
{
    this->setZValue(this->zValue() - 1);
}//down level

void MyPixmapItem::setThreshold(int thresholdValue)
{
    this->threshold_value = thresholdValue;
}

int MyPixmapItem::getThreshold()
{
    return this->threshold_value;
}

void MyPixmapItem::cut()
{
    QPixmap src = QPixmap(this->pixmap_o);
    QImage src_data = src.toImage();
    QBitmap mask(src_data.size());

    for(int i = 0; i < src_data.height(); i++)
    {
        for(int j = 0; j < src_data.width(); j++)
        {
            if(qGray(src_data.pixel(j,i)) > threshold_value)
            {
                 src_data.setPixel(j, i, qRgb(0, 0, 0));//imtransparent
            }//threshold value == 50
            else
            {
                src_data.setPixel(j, i, qRgb(255, 255, 255));//transparent
            }
        }
    }//scan by row

    int delta = 25;//extension by 25 pixels
    for(int i = 0; i < src_data.height(); i++)
    {
        for(int j = 0; j < src_data.width(); j++)
        {
           if(src_data.pixel(j,i) != qRgb(255, 255, 255))
           {
                for(int k = 0; k < delta; k++)
                {
                    src_data.setPixel(j + k, i, qRgb(255, 255,255));
                }
                break;//next line
            }
        }
    }//left border extension : scan by row

    for(int i = 0; i < src_data.height(); i++)
    {
        for(int j = src_data.width() - 1; j > 0 ; j--)
        {
           if(src_data.pixel(j,i) != qRgb(255, 255, 255))
           {
                for(int k = 0; k < delta; k++)
                {
                    src_data.setPixel(j - k, i, qRgb(255, 255,255));
                }
                break;
            }
        }
    }//right border extension : scan by row

    mask = QBitmap::fromImage(src_data);//get mask by threshold

    src.setMask(mask);
    setPixmap(src);//update

}//cut pixmap by threshold value

void MyPixmapItem::keyPressEvent(QKeyEvent *event)
{
    QGraphicsItem::keyPressEvent(event);
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_M)
    {
        updateMode();
    }//switch modes
}

void MyPixmapItem::setPixmap(const QPixmap &pixmap)
{
    this->pixmap = QPixmap(pixmap);
    if(pixmap.height() > 400 || pixmap.width() > 400){
        QSize maxSize(400, 400);
        this->pixmap = pixmap.scaled(maxSize, Qt::KeepAspectRatio);
    }//limit the max size

    //rect
    int w = trRect->getWidth();
    trRect->setPos( this->pixmap.width() - w/2, -w/2);//in parent coordinates
    blRect->setPos( -w/2, this->pixmap.height() - w/2);
    tlRect->setPos( -w/2, -w/2);
    brRect->setPos( this->pixmap.width() - w/2, this->pixmap.height() - w/2);
    clRect->setPos( -w/2, this->pixmap.height()/2);
    crRect->setPos( this->pixmap.width() - w/2, this->pixmap.height()/2);
    tRect->setPos( this->pixmap.width()/2, -w/2);
    bRect->setPos( this->pixmap.width()/2, this->pixmap.height() - w/2);
    cRect->setPos( this->pixmap.width()/2, this->pixmap.height()/2);


}
