#include "areascene.h"

AreaScene::AreaScene(QObject *parent, int size)
    : QGraphicsScene{parent}, m_size(size)
{
    setGrid();
}

AreaScene::~AreaScene(){

}

void AreaScene::setGrid()
{
    for (int i = 0; i < m_size; ++i) {
        addLine(0,i * 50, (m_size-1) * 50, i*50, QPen(Qt::gray));
        addLine(i * 50,0, i * 50, (m_size-1) * 50, QPen(Qt::gray));
    }
}

void AreaScene::setSceneSize(int size)
{
    this->m_size = size;
    foreach (auto e, m_entities) { // détache les objets de la scène
        removeItem(e);
    }
    this->clear(); // efface la scène
    setGrid(); // reconstruit la scène avec les bonnes dimensions

    foreach (Entity* e, m_entities) { // réajoute les objets qui ont été détaché
        for (int i = 0; i < m_nObject; ++i) {
            QGraphicsScene::addItem(e);
            e->setPos(m_nObject * 50, 0);
        }
    }
}

int AreaScene::getSceneSize()
{
    return m_size;
}

void AreaScene::addPlayer()
{
    Entity* entity = new Player();
    entity->setPos(m_nObject * 50, 0);
    m_entities.append(entity);
    m_objects.append(entity);
    QGraphicsScene::addItem(entity);

    entity->setData(0, QString("Player %1").arg(m_nEntity));

    entity->setm_initialX(entity->pos().x());
    entity->setm_initialY(entity->pos().y());

    m_nObject++;
    m_nEntity++;
}

void AreaScene::addPnj(bool ennemie)
{
    Entity* entity = new PNJ(10, 1, ennemie);
    entity->setPos(m_nObject * 50, 0);
    m_entities.append(entity);
    m_objects.append(entity);
    QGraphicsScene::addItem(entity);

    if(ennemie == false)
    {
        entity->setData(0, QString("PNJ %1").arg(m_nEntity));
    }
    else
    {
        entity->setData(0, QString("Ennemie %1").arg(m_nEntity));
    }


    entity->setm_initialX(entity->pos().x());
    entity->setm_initialY(entity->pos().y());

    m_nObject++;
    m_nEntity++;
}

void AreaScene::addPItem()
{
    Item* item = new Item(Qt::yellow, 25, 25, "None");
    item->setPos(m_nObject * 50, 0);
    item->setPos(item->pos().x() + 12, item->pos().y() + 12);
    m_items.append(item);
    m_objects.append(item);
    QGraphicsScene::addItem(item);

    item->setData(0, QString("Item %1").arg(m_nItem));

    m_nObject++;
    m_nItem++;
}

void AreaScene::setm_nObject(int n)
{
    m_nObject = n;
}

int AreaScene::getm_nObject()
{
    return m_nObject;
}

void AreaScene::deplacementObject(QString entityData)
{
    bool finish = false;
    foreach (auto e, m_entities) {
        if(finish == true)
        {
            break;
        }

        int x = (e->pos().x() + 25) - ((int)(e->pos().x() + 25) % 50); // quand la souris est relaché, la position de l'item est récupéré, avec '.x()' et '.y()'
        // puis retire son modulo de 50, pour que l'item retourne à un multiple de 50, donc à une case
        // le + 25 (moitié de 50, permet à ce que ce soit par rapport au centre de l'item, qu'il soit replacé
        int y = (e->pos().y() + 25) - ((int)(e->pos().y() + 25) % 50);

        if(x <= e->getm_initialX()+e->getm_sizeStep() && x >= e->getm_initialX()-e->getm_sizeStep()
            && y <= e->getm_initialY()+e->getm_sizeStep() && y >= e->getm_initialY()-e->getm_sizeStep())
        {
            e->setPos(x, y);
            foreach (auto i, m_items) {
                int x = (i->pos().x() + 25) - ((int)(i->pos().x() + 25) % 50);
                int y = (i->pos().y() + 25) - ((int)(i->pos().y() + 25) % 50);
                i->setPos(x, y);
                if(e->pos() == i->pos())
                {
                    i->setPos(i->pos().x()+12, i->pos().y()+12);
                    i->activateEvent(e);
                    removeItem(i);
                    finish = true;
                    break;
                }
                else
                {
                    i->setPos(i->pos().x()+12, i->pos().y()+12);
                }
            }
            foreach (auto e2, m_entities) {
                if(e->pos() == e2->pos() && e != e2 && e->data(0).toString().contains(entityData) && entityData != "PNJ")
                {
                    qDebug() << "e" << e->pos();
                    qDebug() << "e2" << e2->pos();
                    e->attack(e2);
                    e->setPos(e->getm_initialX(), e->getm_initialY());
                    qDebug() << "e" << e->pos();
                    finish = true;
                    break;
                }
            }
            e->setm_initialX(x);
            e->setm_initialY(y);
        }
        else
        {
            e->setPos(e->getm_initialX(), e->getm_initialY());
        }
    }
}

void AreaScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    deplacementObject("Player");
    QGraphicsScene::mouseReleaseEvent(e);
}

void AreaScene::testDeplacement(Entity *e, int x, int y)
{
    e->setPos(x, y);
}




