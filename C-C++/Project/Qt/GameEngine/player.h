#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player(int PV = 10, int attackPoint = 1);

};
#endif // PLAYER_H
