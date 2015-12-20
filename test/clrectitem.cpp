#include "CLRectItem.h"
#include "mypixmapitem.h"
CLRectItem::CLRectItem()
{
    //initialize the width
    width = 8;

    //initialize the drawing mode: f-move t-rotate
    mode = false;
    updateCursor();

    //setMovable
   // this->setFlag(ItemIsMovable);
}

QRectF CLRectItem::boundingRect() const
{
    return QRectF(0, 0, width, width);
}

void CLRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //draw the rect
    painter->setPen(Qt::DashDotLine);
    painter->drawRect(boundingRect());

}

void CLRectItem::updateMode()
{
    mode = !mode;
    updateCursor();
}//change now mode

void CLRectItem::setMode(bool mode)
{
    this->mode = mode;
    updateCursor();
}

int CLRectItem::getWidth()
{
    return width;
}


void CLRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //redraw
    update();

  //  QGraphicsItem::mousePressEvent(event);
}

void CLRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->parentItem()->hasFocus())
    {
        QPointF center = dynamic_cast<MyPixmapItem*>(this->parentItem())-> getCenter();
        QTransform* transform = new QTransform();
        transform->translate(center.x(), center.y());


        QPointF oldPos = scenePos();
        QPointF newPos = event->scenePos();
        qreal distance;
        int delta = this->pos().x() - (-width/2) > 0 ? 1 : -1;//cr:1
        if(!mode)
        {
            distance = (newPos.x() - oldPos.x())* 0.005 * delta;//cr
            distance = distance < -width ?  -width: distance;
            transform->scale(1 + distance/width, 1);
        }//move
        else if(mode)
        {
            distance = (newPos.y() - oldPos.y())* 0.003 * delta;//cr
            transform->shear(0, distance/width);
        }//rotate clockWise

        transform->translate(-center.x(), -center.y());
        this->parentItem()->setTransform(*transform, true);
        update();
    }

}// QGraphicsItem::mouseMoveEvent(event);


void CLRectItem::updateCursor()
{
    if(!mode)//move
        this -> setCursor(Qt::SizeHorCursor);
    else//rotate
        this -> setCursor(QCursor(QPixmap("../test/img/CL_R.png")));
}//switch cursor according to the mode

