#ifndef MASCENE_H
#define MASCENE_H

#include <QObject>
#include <QGraphicsView>
#include "monrectitem.h"

class MaScene : public QGraphicsScene
{
public:
    MaScene(QObject* parent = Q_NULLPTR);
    ~MaScene(); // pour détruire tout ce que contient la liste d'item 'm_items' SI l'objet n'est pas ajouté dans une scène

    QList<MonRectItem*> m_items;
};

#endif // MASCENE_H
