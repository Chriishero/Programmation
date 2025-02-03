#include "monrectitem.h"
#include <QPen>
#include <QDebug>

MonRectItem::MonRectItem()
{
    setRect(0,0 ,50,50); // définie la postion x,y et la taille x,y de l'item
    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::red)); // définie l'item comme étant rouge

    setFlag(QGraphicsItem::ItemIsMovable); // définie l'item comme déplaçable
    setFlag(QGraphicsItem::ItemIsSelectable); // définie l'item comme sélectionnable
}

MonRectItem::~MonRectItem()
{
    qDebug() << "Item destroyed." << Qt::endl; // est affiché si c'est la scène qui s'occupe de la destruction des items.
}

void MonRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    int x = (pos().x() + 25) - ((int)(pos().x() + 25) % 50); // quand la souris est relaché, la position de l'item est récupéré, avec '.x()' et '.y()'
    // puis retire son modulo de 50, pour que l'item retourne à un multiple de 50, donc à une case
    // le + 25 (moitié de 50, permet à ce que ce soit par rapport au centre de l'item, qu'il soit replacé
    int y = (pos().y() + 25) - ((int)(pos().y() + 25) % 50);

    setPos(x,y); // l'item est positionné pile dans la case la plus proche, par rapport au centre de l'item
    QGraphicsRectItem::mouseReleaseEvent(e);
}
