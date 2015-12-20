#ifndef CLRECTITEM_H
#define CLRECTITEM_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class CLRectItem : public QGraphicsItem
{
public:
    CLRectItem();
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

#endif // CLRECTITEM_H
