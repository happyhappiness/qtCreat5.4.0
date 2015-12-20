#ifndef TRECTITEM_H
#define TRECTITEM_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class TRectItem : public QGraphicsItem
{
public:
    TRectItem();
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void updateMode();
    void setMode(bool mode);
    int getWidth();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    int width;
    bool mode;
    void updateCursor();
};

#endif // TRECTITEM_H
