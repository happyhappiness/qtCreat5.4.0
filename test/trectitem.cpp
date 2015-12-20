#include "TRectItem.h"
#include "mypixmapitem.h"
TRectItem::TRectItem()
{
    //initialize the width
    width = 8;

    //initialize the drawing mode: f-move t-rotate
    mode = false;
    updateCursor();

    //setMovable
   // this->setFlag(ItemIsMovable);
}

QRectF TRectItem::boundingRect() const
{
    return QRectF(0, 0, width, width);
}

void TRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //draw the rect
    painter->setPen(Qt::DashDotLine);
    painter->drawRect(boundingRect());

}

void TRectItem::updateMode()
{
    mode = !mode;
    updateCursor();
}//change now mode

void TRectItem::setMode(bool mode)
{
    this->mode = mode;
    updateCursor();
}

int TRectItem::getWidth()
{
    return width;
}


void TRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //redraw
    update();
}

void TRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->parentItem()->hasFocus())
    {
        QPointF center = dynamic_cast<MyPixmapItem*>(this->parentItem())-> getCenter();
        QTransform* transform = new QTransform();
        transform->translate(center.x(), center.y());


        QPointF oldPos = scenePos();
        QPointF newPos = event->scenePos();
        qreal distance;
        int delta =  this->pos().y() - (-width/2) > 0 ? 1 : -1;//b = 1
        if(!mode)
        {
            distance = (newPos.y() - oldPos.y())* 0.03 * delta;//t&b
            distance = distance < -width ?  -width : distance;
            transform->scale(1, 1 + distance/width);
        }//scale
        else if(mode)
        {
            distance = (newPos.x() - oldPos.x())* 0.003 * delta;//t&b
            transform->shear( distance/width, 0);
        }//shear

        transform->translate(-center.x(), -center.y());
        this->parentItem()->setTransform(*transform, true);
        update();
    }

}// QGraphicsItem::mouseMoveEvent(event);

void TRectItem::updateCursor()
{
    if(!mode)//move
        this -> setCursor(Qt::SizeVerCursor);
    else//rotate
        this -> setCursor(QCursor(QPixmap("../test/img/T_R.png")));
}//switch cursor according to the mode

