#include "player.h"
#include <QPen>

Player::Player(int PV, int attackPoint) : Entity(PV, attackPoint)
{
    setRect(0,0, 50, 50);
    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::white));
}
