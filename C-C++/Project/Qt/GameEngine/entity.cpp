#include "entity.h"
#include <QPen>

Entity::Entity(int PV, int attackPoint) : m_PV(PV), m_attackPoint(attackPoint)
{
    m_initialPV = PV;
    m_initialAttackPoint = attackPoint;
}

void Entity::setm_initialX(int n)
{
    m_initialX = n;
}

void Entity::setm_initialY(int n)
{
    m_initialY = n;
}

int Entity::getm_initialX()
{
    return m_initialX;
}
int Entity::getm_initialY()
{
    return m_initialY;
}

int Entity::getm_beforeX()
{
    return m_beforeX;
}

int Entity::getm_beforeY()
{
    return m_beforeY;
}

void Entity::setm_sizeStep(int n)
{
    m_sizeStep = 50*n;
}

int Entity::getm_sizeStep()
{
    return m_sizeStep;
}

void Entity::setm_PV(int n)
{
    m_PV = n;
}

int Entity::getm_PV()
{
    return m_PV;
}

int Entity::getm_initialPV()
{
    return m_initialPV;
}

int Entity::getm_initialAttackPoint()
{
    return m_initialAttackPoint;
}

int Entity::setm_initialPV(int n)
{
    m_initialPV = n;
}

int Entity::setm_initialAttackPoint(int n)
{
    m_initialAttackPoint = n;
}

void Entity::setm_attackPoint(int n)
{
    m_attackPoint = n;
}

int Entity::getm_attackPoint()
{
    return m_attackPoint;
}

void Entity::attack(Entity* e)
{
    e->setm_PV(e->getm_PV()-getm_attackPoint());
    qDebug() << this->data(0).toString() << " a infligé " << getm_attackPoint() << " à " << e->data(0).toString();
}

void Entity::setdeplacement_frequence(int n)
{
    m_deplacement_frequence = n;
}

int Entity::getdeplacement_frequence()
{
    return m_deplacement_frequence;
}

void Entity::setdeplacement_patern(QString p)
{
    m_deplacement_patern = p;
}

QString Entity::getdeplacement_patern()
{
    return m_deplacement_patern;
}

void Entity::deplacement(int x, int y)
{
    this->setPos(x, y);
}

void Entity::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    qDebug() << "step size : " << getm_sizeStep();

    m_beforeX = pos().x();
    m_beforeY = pos().y();

    int x = (pos().x() + 25) - ((int)(pos().x() + 25) % 50); // quand la souris est relaché, la position de l'item est récupéré, avec '.x()' et '.y()'
    // puis retire son modulo de 50, pour que l'item retourne à un multiple de 50, donc à une case
    // le + 25 (moitié de 50, permet à ce que ce soit par rapport au centre de l'item, qu'il soit replacé
    int y = (pos().y() + 25) - ((int)(pos().y() + 25) % 50);

    if(x <= m_initialX+m_sizeStep && x >= m_initialX-m_sizeStep && y <= m_initialY+m_sizeStep && y >= m_initialY-m_sizeStep)
    {
        setPos(x,y); // l'item est positionné pile dans la case la plus proche, par rapport au centre de l'item
        m_initialX = x;
        m_initialY = y;
        qDebug() << "x : " << pos().x() << " y : " << pos().y();
    }
    else
    {
        setPos(m_initialX, m_initialY);
    }
    /*foreach (auto i, m_items) {
        if(i.pos().x()-12 == x && i.pos().y()-12 == y)
        {
            qDebug() << "yeeeeeee";
        }
    }*/
    QGraphicsRectItem::mouseReleaseEvent(e);
}

int Entity::getcoutdownDeplacement()
{
    return coutdownDeplacement;
}

void Entity::setcoutdownDeplacement(int n)
{
    coutdownDeplacement = n;
}
