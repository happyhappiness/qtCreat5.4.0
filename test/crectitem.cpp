#include "crectitem.h"

CRectItem::CRectItem()
{
    //initialize the width
    width = 8;

    //initialize the drawing mode: f-move t-rotate
    this->setCursor(Qt::SizeAllCursor);

}//initialize

QRectF CRectItem::boundingRect() const
{
    return QRectF(0, 0, width, width);
}

void CRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //draw the rect
    painter->setPen(Qt::DashDotLine);
    painter->drawRect(boundingRect());

}

int CRectItem::getWidth()
{
    return width;
}

void CRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->parentItem()->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->parentItem()->setFlag(QGraphicsItem::ItemIsMovable);
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void CRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

