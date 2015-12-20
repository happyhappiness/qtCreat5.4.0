#include "myrectitem.h"
#include "mypixmapitem.h"
MyRectItem::MyRectItem()
{
    //initialize the width
    width = 8;

    //initialize the drawing mode: f-move t-rotate
    mode = false;
    updateCursor();

    //setMovable
   this->setAcceptHoverEvents(true);
}

QRectF MyRectItem::boundingRect() const
{
    return QRectF(0, 0, width, width);
}

void MyRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //draw the rect
    painter->setPen(Qt::DashDotLine);
    painter->drawRect(boundingRect());
}

void MyRectItem::updateMode()
{
    mode = !mode;
    updateCursor();
}//change now mode

void MyRectItem::setMode(bool mode)
{
    this->mode = mode;
    updateCursor();
}

int MyRectItem::getWidth()
{
    return width;
}


void MyRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //redraw
    update();
  //  QGraphicsItem::mousePressEvent(event);
}

void MyRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
                distance = (oldPos.y() - newPos.y())* 0.03;//tr
            else
                distance = (newPos.y() - oldPos.y())* 0.03;//bl
            distance = distance < -width ?  -width : distance;
            transform->scale(1 + distance/width, 1 + distance/width);
        }//move
        else if(mode)
        {
            transform->rotate(1);
        }//rotate clockWise

        transform->translate(-center.x(), -center.y());
         this->parentItem()->setTransform(*transform, true);
        update();
    }

}

void MyRectItem::updateCursor()
{
    if(!mode)//move
        this -> setCursor(Qt::SizeBDiagCursor);
    else//rotate
        this -> setCursor(QCursor(QPixmap("../test/img/TR_R.png")));
}//switch cursor according to the mode

