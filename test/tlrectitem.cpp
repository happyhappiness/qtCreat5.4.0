#include "TLRectItem.h"
#include "mypixmapitem.h"

TLRectItem::TLRectItem()
{
    //initialize the width
    width = 8;

    //initialize the drawing mode: f-move t-rotate
    mode = false;
    updateCursor();

    //setMovable
   // this->setFlag(ItemIsMovable);
}

QRectF TLRectItem::boundingRect() const
{
    return QRectF(0, 0, width, width);
}

void TLRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //draw the rect
    painter->setPen(Qt::DashDotLine);
    painter->drawRect(boundingRect());

}

void TLRectItem::updateMode()
{
    mode = !mode;
    updateCursor();
}//change now mode

void TLRectItem::setMode(bool mode)
{
    this->mode = mode;
    updateCursor();
}

int TLRectItem::getWidth()
{
    return width;
}


void TLRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //redraw
    update();

  //  QGraphicsItem::mousePressEvent(event);
}

void TLRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->parentItem()->hasFocus())
    {
        QPointF center = dynamic_cast<MyPixmapItem*>(this->parentItem())-> getCenter();
        QTransform* transform = new QTransform();
        transform->translate(center.x(), center.y());

        if(!mode)
        {
            QPointF oldPos = scenePos();
            QPointF newPos = event->scenePos();
            qreal distance;
            if(this->pos().y() == -width/2)
                distance = (oldPos.y() - newPos.y())* 0.03;//tl
            else
                distance = (newPos.y() - oldPos.y())* 0.03;//br
            distance = distance < -width ?  -width : distance;
            transform->scale(1 + distance/width, 1 + distance/width);
        }//move
        else if(mode)
        {
            transform->rotate(-1);
        }//rotate clockWise

        transform->translate(-center.x(), -center.y());
        this->parentItem()->setTransform(*transform, true);
        update();
    }

}// QGraphicsItem::mouseMoveEvent(event);

void TLRectItem::updateCursor()
{
    if(!mode)//move
        this -> setCursor(Qt::SizeFDiagCursor);
    else//rotate
        this -> setCursor(QCursor(QPixmap("../test/img/TL_R.png")));
}//switch cursor according to the mode

