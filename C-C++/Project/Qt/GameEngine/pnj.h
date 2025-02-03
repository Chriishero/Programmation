#ifndef PNJ_H
#define PNJ_H

#include "entity.h"

class PNJ : public Entity
{
public:
    PNJ(int PV = 10, int attackPoint = 1, bool ennemie = true);

    void setattack_frequence(int n);
    int getattack_frequence();

private:
    bool m_ennemie;
};

#endif // PNJ_H
