#ifndef AREASCENE_H
#define AREASCENE_H

#include <QGraphicsView>
#include <QObject>
#include "gameobject.h"
#include "entity.h"
#include "player.h"
#include "pnj.h"
#include "item.h"

class AreaScene : public QGraphicsScene
{
public:
    AreaScene(QObject *parent = Q_NULLPTR, int size = 10);
    ~AreaScene();

    QList<GameObject*> m_objects;
    QList<Entity*> m_entities;
    QList<Item*> m_items;

public slots:
    void setGrid();
    void setSceneSize(int size);
    int getSceneSize();

    void addPlayer();
    void addPnj(bool ennemie);
    void addPItem();

    void setm_nObject(int n);
    int getm_nObject();

    void deplacementObject(QString entityData);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
    void testDeplacement(Entity* e, int x, int y);
    //void focusInEvent(QFocusEvent *e);

private:
    int m_size;
    int m_nObject = 0;
    int m_nEntity = 0;
    int m_nItem = 0;
};

#endif // AREASCENE_H
