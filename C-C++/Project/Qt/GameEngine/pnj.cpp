#include "pnj.h"
#include <QPen>

PNJ::PNJ(int PV, int attackPoint, bool ennemie) : Entity(PV, attackPoint), m_ennemie(ennemie)
{
    setRect(0,0, 50, 50);
    setPen(QPen(Qt::black));
    if(ennemie == false)
    {
        setBrush(QBrush(Qt::blue));
    }
    else{
        setBrush(QBrush(Qt::red));
    }
}
