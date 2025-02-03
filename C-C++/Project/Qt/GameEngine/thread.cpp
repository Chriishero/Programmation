#include "thread.h"

thread::thread() {}

void thread::checkCondition()
{
    qDebug() << "putain";
    foreach (auto c, winConditionList) {
        QList<QString> condition = c.split("|");
        Entity* entity;
        int* attribut = nullptr;
        int target = condition[4].toInt();;
        foreach (auto e, condition) {
            qDebug() << e;
        }

        foreach (auto o, m_scene->m_entities) {
            qDebug("test");
            if(o->data(0).toString().contains(condition[1]))
            {
                entity = o;
            }
        }
        if(condition[2] == "PV")
        {
            *attribut = entity->getm_PV();
        }
        if(condition[3] == "==")
        {
            if(*attribut == target)
            {
                qDebug() << "You Win";
                stopGame();
            }
        }
    }
}
