#ifndef ENTITY_H
#define ENTITY_H

#include "gameobject.h"

class Entity : public GameObject
{
public:
    Entity(int PV = 10, int attackPoint = 1);

public slots:
    void setm_initialX(int n);
    void setm_initialY(int n);
    int getm_initialX();
    int getm_initialY();
    int getm_beforeX();
    int getm_beforeY();

    void setm_sizeStep(int n);
    int getm_sizeStep();

    void setm_PV(int n);
    int getm_PV();

    int getm_initialPV();
    int getm_initialAttackPoint();
    int setm_initialPV(int n);
    int setm_initialAttackPoint(int n);

    void setm_attackPoint(int n);
    int getm_attackPoint();

    void attack(Entity* e);
    void setdeplacement_frequence(int n);
    int getdeplacement_frequence();

    void setdeplacement_patern(QString p);
    QString getdeplacement_patern();

    void deplacement(int x, int y);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);

    int getcoutdownDeplacement();
    void setcoutdownDeplacement(int n);

private:
    int m_PV;
    int m_attackPoint;
    int m_initialPV;
    int m_initialAttackPoint;

    int m_initialX = pos().x();
    int m_initialY = pos().y();
    int m_beforeX;
    int m_beforeY;

    int m_sizeStep = 50;
    int m_deplacement_frequence = 0;

    QString m_deplacement_patern = "Random";

    int coutdownDeplacement = 0;
};

#endif // ENTITY_H
