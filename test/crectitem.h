#ifndef CRECTITEM_H
#define CRECTITEM_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class CRectItem : public QGraphicsItem
{
public:
    CRectItem();
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    int getWidth();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int width;
};

#endif // CRECTITEM_H
