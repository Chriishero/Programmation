#ifndef MONRECTITEM_H
#define MONRECTITEM_H

#include <QGraphicsRectItem>

class MonRectItem : public QGraphicsRectItem
{
public:
    MonRectItem();
    ~MonRectItem();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);

};

#endif // MONRECTITEM_H
