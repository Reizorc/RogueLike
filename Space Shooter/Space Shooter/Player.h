#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player: public Entity
{
public:
    int moveSpeed = 4;

    Player();
    void movement();
};

#endif // PLAYER_H
