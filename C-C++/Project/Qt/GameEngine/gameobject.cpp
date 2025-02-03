#include "gameobject.h"

GameObject::GameObject() {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void GameObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    int x = (pos().x() + 25) - ((int)(pos().x()+12) % 50); // quand la souris est relaché, la position de l'item est récupéré, avec '.x()' et '.y()'
    // puis retire son modulo de 50, pour que l'item retourne à un multiple de 50, donc à une case
    // le + 25 (moitié de 50, permet à ce que ce soit par rapport au centre de l'item, qu'il soit replacé
    int y = (pos().y() + 25) - ((int)(pos().y()+12) % 50);

    setPos(x, y);

    QGraphicsRectItem::mouseReleaseEvent(e);
}
