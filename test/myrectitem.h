#ifndef MYRECTITEM_H
#define MYRECTITEM_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class MyRectItem : public QGraphicsItem
{
public:
    MyRectItem();
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void updateMode();
    void setMode(bool mode);
    int getWidth();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


private:
    int width;
    bool mode;
    void updateCursor();
};

#endif // MYRECTITEM_H
