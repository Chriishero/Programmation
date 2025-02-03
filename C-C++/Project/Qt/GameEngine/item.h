#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include "gameobject.h"
#include "entity.h"

class Item : public GameObject
{
public:
    Item(QColor color, int Hsize, int Lsize, QString event);

    void setm_color(QColor color);
    QColor getm_color();

    void setm_Hsize(int size);
    int getm_Hsize();

    void setm_Lsize(int size);
    int getm_Lsize();

    void setm_event(QString e);
    QString getm_event();
    void activateEvent(Entity* e);
    void setn_Event(int n);
    int getn_Event();

private:
    QColor m_color;
    int m_Hsize;
    int m_Lsize;
    QString m_event;

    int n_heal = 2;
    int n_buffAttack = 2;
    int n_buffStepSize = 1;
    int n_inflictsDamage = 10;
    int n_debuffAttack = 2;
    int n_debuffStepSize = 1;
};

#endif // ITEM_H
