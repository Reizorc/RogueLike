#ifndef MISSILE_H
#define MISSILE_H

#include "Entity.h"


class missile: public Entity
{
    public:
        missile();
        void updatePosition();
        bool isDestroyed;
        int moveSpeed = 10;
    protected:
    private:
};

#endif // MISSILE_H
