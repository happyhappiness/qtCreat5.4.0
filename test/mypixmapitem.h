#ifndef MYPIXMAPITEM_H
#define MYPIXMAPITEM_H

#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include "myrectitem.h"
#include "crectitem.h"
#include "clrectitem.h"
#include "tlrectitem.h"
#include "trectitem.h"

class MyPixmapItem : public QGraphicsItem
{
public:
    MyPixmapItem();
    ~MyPixmapItem();
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void setPixmap_o(const QPixmap& pixmap_o);
    QPointF getCenter();

    void updateMode();
    void setMode(bool mode);

    void upLevel();
    void downLevel();

    void setThreshold(int thresholdValue);
    int getThreshold();
    void cut();//bool cutted;

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    MyRectItem* trRect;
    MyRectItem* blRect;
    TLRectItem* tlRect;
    TLRectItem* brRect;
    CLRectItem* clRect;
    CLRectItem* crRect;
    TRectItem* tRect;
    TRectItem* bRect;
    CRectItem* cRect;

    QGraphicsPixmapItem* pixmapItem;
    QPixmap pixmap;//for show
    QPixmap pixmap_o;//for origin keep
    int threshold_value;


    void setPixmap(const QPixmap& pixmap);//change the pixmap

};

#endif // MYPIXMAPITEM_H
