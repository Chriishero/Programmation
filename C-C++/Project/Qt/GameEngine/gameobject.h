#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsRectItem>
#include <QObject>

class GameObject : public QGraphicsRectItem
{
public:
    GameObject();

protected slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

};

#endif // GAMEOBJECT_H
